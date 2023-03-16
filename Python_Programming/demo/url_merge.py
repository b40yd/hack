
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist,squareform

api_endpoint_i = 0
host_i = 1
port_i = 2
method_i = 3
ApiMetricInfo_i = -2
hasMerged_i = -1


def metricStrHasNumeric(a,b):

    def isVerNo(str):
        import re
        pattern = r'^\d+(\.\d+){0,10}$'
        rt = re.search(pattern, str)
        if rt:
            return True
        return False

    #都是纯数字
    if a.isnumeric() and b.isnumeric():
        return 1
    
    # #版本号格式
    # if isVerNo(a) and isVerNo(b):
    #     return 1
    
    #字母和特殊字符位置固定，只有数字变化，比如前缀DAP-111
    if len(a) == len(b):
        similar = True
        for i in range(len(a)):
            x = a[i]
            y = b[i]
            if x == y:
                continue
            if x.isnumeric() and y.isnumeric():
                continue
            similar = False
            break

        if similar:
            return 1
        else:
            return 2
        
    #普通的包含数字的字符,长度也不相等的场景
    return 3

def metricStrSameLen(a,b):
    #全是字母
    if a.isalpha() or b.isalpha():
        return 3

    #特殊字符位置固定，只有字母变化
    similar = True
    for i in range(len(a)):
        x = a[i]
        y = b[i]
        if x == y:
            continue
        if x.isalpha() and y.isalpha():
            continue
        similar = False
        break
    if similar:
        return 2
    #特殊字符位置固定，只有字母变化

    return 3

def havenumeric(str):
    if str == 'undefined':
        return True
    
    for x in str:
        if x.isdigit():
            return True
    return False

def isFileName(a, b):
    if a.endswith(".json") and b.endswith(".json"):
        return True

def isHostName(a, b):
    def startInList(str):
        list = ["com.", "de.", "org.", "ru.", "info.", "is.", "logjira."]
        for x in list:
            if str.startswith(x):
                return True
        return False

    if startInList(a) and startInList(b):
        return True

def apimetric(u, v):
    """
    距离计算基本策略：
    0 ：完全相同、都是模板{}、有一个是*结束
    1 ：纯数字、版本号格式、有数字编号（长度相同，且字母和特殊字符位置固定，只有数字变化，比如前缀DAP-111）
    2 ：包含数字但长度不同、无数字编号(长度相同，特殊字符位置固定，只有字母变化)
    3 ：长度相同且无数字
    4 ：非最后一级默认
    5 ：最后一级默认，最后一级容易误判，因此高一点。
    """
    ## host
    if u[host_i] != v[host_i]:
        return 100
    
    ## method
    if u[method_i] != v[method_i]:
        return 100

    x = u[ApiMetricInfo_i].splited
    y = v[ApiMetricInfo_i].splited
    #长度不不同，且没有*结束的无法聚类。
    if len(x) != len(y) and  x[-1] != '*' and y[-1] != '*':
        return 100
    
    #遍历path每一层
    a_havenum_list =  u[ApiMetricInfo_i].havenumeric
    b_havenum_list =  v[ApiMetricInfo_i].havenumeric
    length = min(len(x),len(y))
    dist = 0
    for i in range(length) :
        a = x[i]
        b = y[i]

        #完全相等
        if a == b:
            continue

        if a == '' or b == '':
            break

        #处理结尾的 *     
        if a == "*" or b == "*":
            return dist
        
        # 都是模板{}
        if a[0] == '{' or b[0] == '{':
            if a[0] == '{' and b[0] == '{':
                pass
            elif (a[0] == '{' and b_havenum_list[i]) or \
                 (b[0] == '{' and a_havenum_list[i]):
                dist += 1
            else:
                 dist += 2
            continue
        
        #包含数字的
        if a_havenum_list[i] and b_havenum_list[i]:
            dist += metricStrHasNumeric(a, b)
            continue
    
        #长度相同的字符串，则比较每个字符类型是否一样
        if len(a) == len(b):
            # dist += metricStrSameLen(a, b)
            dist += 3
            continue

        #最后一级且后缀名一样 加分少一些？？
        if i == length -1:
            dist += 5
            # if isFileName(a, b):
            #     dist += 3
            # else:
            #     dist += 5
        
        #默认距离
        dist += 4
    

    return dist + (abs(len(x)-len(y)) *5)


class ApiMetricInfo:
    def __init__(self, api_endpoint):
        self.splited = (api_endpoint.split('/'))[1:]
        self.havenumeric = []
        for str in self.splited:
            self.havenumeric.append(havenumeric(str))
    
###### 读取测试数据
##### X: [api_endpoint, host, port, method,  ApiMetricInfo(-2), hasMerged(-1)]
def read_csv(fn,max_num=1000):
    import csv
    rt = []
    
    with open(fn, encoding='utf-8')as f:
        reader = csv.reader(f)
        headers = next(reader)
        print(headers)

        # for i in range(300):
        #     next(reader)
        
        num = 0
        for row in reader:
            api_endpoint = row[0]
            host = row[1]
            port = row[2]
            method = row[3]
            rt.append([api_endpoint, host, port, method, ApiMetricInfo(api_endpoint), False])
            num += 1
            if num >max_num:
                break
    return rt

###### 尝试合并出模板API
def merge(cluster_samples, distance):
    """
    distance: 集群内最大距离。距离越大，需要的不同样例越多。
    """
    def longestCommonPrefix(strs):
        if not strs: return ""
        str0 = min(strs)
        str1 = max(strs)
        for i in range(len(str0)):
            if str0[i] != str1[i]:
                return str0[:i]
        return str0
    
    class SectionInfo:
        def __init__(self):
            self.str_set = set()
            self.has_star = False
            self.has_template = False
            self.prefix = ""

    #汇总信息
    sections = []
    for sample in cluster_samples:
        splited = sample[ApiMetricInfo_i].splited
        for i in range(len(splited)):
            if i >= len(sections):
                sections.append(SectionInfo())
                sections[i].prefix = splited[i]

            if splited[i] == "*":
                sections[i].has_star = True
                continue
            elif splited[i].startswith('{'):
                sections[i].has_template =True
                continue

            if sections[i].prefix:
                sections[i].prefix = longestCommonPrefix([sections[i].prefix, splited[i]])
            
            sections[i].str_set.add(splited[i])
    
    #生成新的API
    newApi = "{} {}:{}".format(cluster_samples[0][method_i], cluster_samples[0][host_i],  cluster_samples[0][port_i])
    min_difference_samples = 10
    if distance >= 4:
        min_difference_samples = 15


    id_index = 1
    for s in sections:
        if s.has_template:
            newApi = newApi + '/' + "{id" + str(id_index) + "}"
            id_index += 1
            continue

        if s.has_star:
            newApi = newApi + '/*' 
            break

        #     min_difference_sample = 10
        # if len(s.prefix) >= 2:

        str_set_len = len(s.str_set)
        if  str_set_len == 1:
            newApi = newApi  + '/' + s.str_set.pop()
        elif  str_set_len > min_difference_samples :
            newApi = newApi + '/' + "{id" +  str(id_index) + '('+ s.prefix  +')'+ "}"
            id_index += 1
        else:
            return None

    return newApi

def cluster_and_merge(fn,max_samples=1000):
    ##### 加载样本
    X = []
    X = read_csv(fn, max_samples)
    print('===========加载样本完成============')
    # for i in list:
    #     X.append([i["path"]])
    # X.append(['/api/jira/test/dap-33432'])
    # X.append(['/api/jira/test/dap-53424'])

    # X.append(["/a/b/2"])
    # X.append(["/a/b/3"])
    # X.append(["/a/b/*"])

    ###### 计算距离矩阵
    Y = pdist(X, apimetric)
    print('===========距离矩阵构造完成============')
    print(squareform(Y))

    ###### SciPy层次聚类实现
    from scipy.cluster.hierarchy import linkage

    #其中method参数可以为’single’、’complete’、’average’、’weighted’、’centroid’、’median’、’ward’中的一种，
    #分别对应我们前面讲到的 Single-link、Complete-link、UPGMA、WPGMA、UPGMC、WPGMC、Ward 方法，
    Z = linkage(Y,  method='weighted')
    print('===========聚类完成============')

    # print(Z.shape)
    # print(Z[: 5])

    ###### 画出树形图
    # from scipy.cluster.hierarchy import dendrogram

    # plt_labels = []
    # for s in X:
    #     plt_labels.append(s[0])
    # plt.figure(figsize=(10, 10))
    # dendrogram(Z, truncate_mode='lastp', p=100,  leaf_rotation=90, leaf_font_size=5, show_contracted=True, labels=plt_labels, )
    # plt.show()
    # return


    ######  查看聚类结果
    from scipy.cluster.hierarchy import fcluster

    ######  打印聚类结果
    # labels_1 = fcluster(Z, t=3, criterion='distance')
    # total_clusters = len(set(labels_1))
    # print("total_clusters : {}".format(total_clusters))  # 看看在该临界距离下有几个 cluster
    # for cl  in range(1, total_clusters+1):
    #     print('cluster no: {}'.format(cl))
    #     for i in range(len(X)):
    #         if cl != labels_1[i]:
    #             continue
    #         print('{} {}:{}{}'.format(X[i][method_i], X[i][host_i],  X[i][port_i], X[i][api_endpoint_i]))

    ######  尝试合并
    newApis = []
    for d in range(2,5):
        print("Max Distance :{}".format(d))
        # Max Distancey越大，要求min_samples_in_cluste越多
        min_samples_in_cluste = 10
        if d >=4 :
            min_samples_in_cluste = 20

        # 根据临界距离返回聚类结果
        labels = fcluster(Z, t=d, criterion='distance')
        clusters = {}
        for i in range(len(labels)):
            if X[i][hasMerged_i] == True:
                continue
            label = str(labels[i])
            if clusters.get(label) is None:
                clusters[label] = []
            clusters[label].append(X[i])

        for cluster in clusters.values():
            if len(cluster) < min_samples_in_cluste:
                continue
            newApi = merge(cluster, d)
            if newApi:
                print("NewApi: {}".format(newApi))
                newApis.append(newApi)
                for s in (cluster):
                    s[hasMerged_i] = True
                    print('{} {}:{}{}'.format(s[method_i], s[host_i],  s[port_i], s[api_endpoint_i]))
                print()

    print(len(newApis))
    diff = {}
    for api in newApis:
        if diff.get(api) is not None:
            continue
        diff[api] = True
        print(api)
    ##是否对newApis二次merge？

if __name__ == '__main__':
    cluster_and_merge("api_list.csv",1000)


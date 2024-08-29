class RadixTree:
    def __init__(self):
        self.root = {}

    def insert(self, method, path, handler):
        node = self.root
        if method not in node:
            node[method] = {}
        node = node[method]
        
        segments = path.split('/')
        for i, segment in enumerate(segments):
            if segment.startswith(':'):
                # 动态参数
                param_name = segment[1:]  # 去掉冒号，获取参数名
                if ':param' not in node:
                    node[':param'] = {'_param_name': param_name}
                node = node[':param']
            elif segment not in node:
                node[segment] = {}
                node = node[segment]
            else:
                node = node[segment]
        node['_handler'] = handler

    def lookup(self, method, path):
        node = self.root
        if method not in node:
            return None
        node = node[method]
        
        params = {}
        segments = path.split('/')
        for segment in segments:
            if segment in node:
                node = node[segment]
            elif ':param' in node:
                node = node[':param']
                params[node.get('_param_name', 'param')] = segment
            else:
                return None, None
        return node.get('_handler'), params

class Router:
    def __init__(self):
        self.tree = RadixTree()

    def add_route(self, method, path, handler):
        self.tree.insert(method, path, handler)

    def route(self, method, path):
        handler, params = self.tree.lookup(method, path)
        if handler:
            return handler(**params)
        else:
            return "404 Not Found"

# 示例用法
def test_router():
    router = Router()
    router.add_route('GET', '/hello', lambda: "你好，世界！")
    router.add_route('GET', '/users/:id', lambda id: f"用户 {id} 的资料")
    router.add_route('POST', '/users', lambda: "创建新用户")

    print(router.route('GET', '/hello'))  # 输出: 你好，世界！
    print(router.route('GET', '/users/123'))  # 输出: 用户 123 的资料
    print(router.route('POST', '/users'))  # 输出: 创建新用户
    print(router.route('GET', '/not/exist'))  # 输出: 404 未找到


# 依赖注入容器
class Container(object):
    def __init__(self):
        self._services = {}

    def register(self, name, instance):
        self._services[name] = instance

    def get(self, name):
        return self._services.get(name)

# 装饰器用于注入依赖
def inject(**dependencies):
    def decorator(func):
        def wrapper(*args, **kwargs):
            for name, service_name in dependencies.items():
                if name not in kwargs:
                    kwargs[name] = container.get(service_name)
            return func(*args, **kwargs)
        return wrapper
    return decorator

# 全局容器实例
container = Container()

# 示例服务
class UserService(object):
    def get_user(self, user_id):
        return "用户 %s" % user_id

class EmailService(object):
    def send_email(self, user, message):
        print("向 %s 发送邮件: %s" % (user, message))

# 注册服务
container.register('user_service', UserService())
container.register('email_service', EmailService())

# 使用依赖注入的示例
@inject(user_service='user_service', email_service='email_service')
def notify_user(user_id, user_service, email_service):
    user = user_service.get_user(user_id)
    email_service.send_email(user, "你有一条新消息")

# 测试依赖注入
def test_di():
    notify_user(123)


# 导入所需的库
from peewee import Model, CharField
from playhouse.pool import PooledPostgresqlExtDatabase
import random

# 定义主写库和多个读库的连接信息
MASTER_DB = {
    'host': '127.0.0.1',
    'port': 5432,
    'user': 'postgres',
    'password': 'meiyoumima',
    'database': 'postgres',
}

SLAVE_DBS = [
    {
        'host': '127.0.0.1',
        'port': 5433,
        'user': 'postgres',
        'password': 'meiyoumima',
        'database': 'postgres',
    },
    {
        'host': '127.0.0.1',
        'port': 5434,
        'user': 'postgres',
        'password': 'meiyoumima',
        'database': 'postgres',
    },
    # 可以添加更多的从库
]

# 创建主写库连接池
master_db = PooledPostgresqlExtDatabase(
    MASTER_DB['database'],
    host=MASTER_DB['host'],
    port=MASTER_DB['port'],
    user=MASTER_DB['user'],
    password=MASTER_DB['password'],
    max_connections=20,
    stale_timeout=300
)

# 创建从库连接池列表
slave_dbs = [
    PooledPostgresqlExtDatabase(
        db['database'],
        host=db['host'],
        port=db['port'],
        user=db['user'],
        password=db['password'],
        max_connections=20,
        stale_timeout=300
    ) for db in SLAVE_DBS
]

class ReadWriteManager:
    def __init__(self, master, slaves):
        self.master = master
        self.slaves = slaves

    def get_read_db(self):
        return random.choice(self.slaves)

    def get_write_db(self):
        return self.master

# 创建读写管理器
db_manager = ReadWriteManager(master_db, slave_dbs)

# 自定义Model基类，实现读写分离
class BaseModel(Model):
    class Meta:
        database = master_db  # 默认使用主库

    @classmethod
    def select(cls, *args, **kwargs):
        cls._meta.database = db_manager.get_read_db()
        return super(BaseModel, cls).select(*args, **kwargs)

    @classmethod
    def insert(cls, *args, **kwargs):
        cls._meta.database = db_manager.get_write_db()
        return super(BaseModel, cls).insert(*args, **kwargs)

    @classmethod
    def update(cls, *args, **kwargs):
        cls._meta.database = db_manager.get_write_db()
        return super(BaseModel, cls).update(*args, **kwargs)

    @classmethod
    def delete(cls, *args, **kwargs):
        cls._meta.database = db_manager.get_write_db()
        return super(BaseModel, cls).delete(*args, **kwargs)

# 示例模型
class User(BaseModel):
    name = CharField()
    email = CharField(unique=True)


def create_user(name, email):
    user, _ = User.get_or_create(name=name, email=email)
    print(f"创建用户：{user.name}")
    
def get_user_by_name_or_email(identifier):
    try:
        user = User.get((User.name == identifier) | (User.email == identifier))
        print(f"找到用户：{user.name}，邮箱：{user.email}")
        return user
    except User.DoesNotExist:
        print(f"未找到用户：{identifier}")
        return None

def get_user(email):
    user = User.get(User.email == email)
    print(f"获取用户：{user.name}")

# 测试读写分离
def test_read_write_separation():
    create_user("张三", "zhangsan@example.com")
    get_user("zhangsan@example.com")

# 更新测试函数
def test_di():
    # notify_user(123)
    test_read_write_separation()


def simple_hash(key):
    """
    实现一个简单的哈希算法
    
    参数:
    key -- 要哈希的字符串

    返回:
    哈希值 (整数)
    """
    hash_value = 0
    for char in key:
        hash_value = (hash_value * 31 + ord(char)) & 0xFFFFFFFF
    return hash_value

# 测试哈希函数
def test_hash():
    test_keys = ["hello", "world", "python", "哈希算法"]
    for key in test_keys:
        print(f"'{key}' 的哈希值: {simple_hash(key)}")

# 在测试函数中添加哈希测试
def test_di():
    test_read_write_separation()
    test_hash()

from tqdm import tqdm
from time import sleep

from colorama import Fore, Style
from rich.progress import track, Progress

from rich.console import Console
console = Console()

test_data = [
    {"jsonrpc": "2.0", "method": "sum", "params": [None, 1, 2, 4, False, True], "id": "1",},
    {"jsonrpc": "2.0", "method": "notify_hello", "params": [7]},
    {"jsonrpc": "2.0", "method": "subtract", "params": [42, 23], "id": "2"},
]

def test_log():
    enabled = False
    context = {
        "foo": "bar",
    }
    movies = ["Deadpool", "Rise of the Skywalker"]
    console.log("Hello from", console, "!")
    console.log(test_data, log_locals=True)

if __name__ == "__main__":
    # test_router()
    # test_di()
    # master_db.create_tables([User])
    # user = User.select().order_by(User.id).get_or_none()
    # print(user.id, user.name, user.email)
    # for i in tqdm(range(100), desc=Fore.GREEN + "Processing" + Style.RESET_ALL):
    #     # 模拟工作
    #     pass
    

    # for step in track(range(100)):
    #     sleep(0.01)

    for i in track(range(20), description="Processing..."):
        sleep(0.01)

    # with Progress() as progress:
    #     task1 = progress.add_task("[red]Downloading...", total=1000)
    #     task2 = progress.add_task("[green]Processing...", total=1000)
    #     task3 = progress.add_task("[cyan]Cooking...", total=1000)

    #     while not progress.finished:
    #         progress.update(task1, advance=0.5)
    #         progress.update(task2, advance=0.3)
    #         progress.update(task3, advance=0.9)
    #         sleep(0.02)

    # from rich import inspect

    # my_list = ["foo", "bar"]

    # inspect(my_list, all=True)
    test_log()

    # console = Console()

    # try:
    #     do_something()
    # except Exception:
    #     console.print_exception(show_locals=True)

    import logging
    from rich.logging import RichHandler
    # 配置日志输出到文件
    import os

    # 确保日志目录存在
    log_dir = "logs"
    # os.makedirs(log_dir, exist_ok=True)

    # 配置文件处理器
    file_handler = logging.FileHandler(os.path.join(log_dir, "app.log"))
    file_handler.setLevel(logging.DEBUG)
    file_formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    file_handler.setFormatter(file_formatter)

    logging.basicConfig(
        level="NOTSET",
        format="%(message)s",
        datefmt="[%X]",
        handlers=[RichHandler(rich_tracebacks=True), file_handler]
    )

    # log = logging.getLogger("rich")
    try:
        print(1 / 0)
    except Exception:
        logging.exception("unable print!")

    from rich import print
    from rich.panel import Panel
    print(Panel("Hello, [red]World!", title="Welcome", subtitle="Thank you"))

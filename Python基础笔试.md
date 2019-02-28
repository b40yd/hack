# Python 笔试题

1.单引号，双引号，三引号的区别？









2.Python的参数传递是值传递还是引用传递？









3.如何以就地操作方式打乱一个列表的元素?









4.字符串格式化:%和.format的区别？











6.写一个函数, 输入一个字符串, 返回倒序排列的结果？
例如:输入"123456"









7.按升序合并如下两个list, 并去除重复的元素?

```python
list1 = [2, 3, 8, 4, 9, 5, 6]
list2 = [5, 6, 10, 17, 11, 2]
```











8.以下的代码的输出将是什么? 说出你的答案并解释。

```python
class Parent(object):
x = 1
class Child1(Parent):
pass
class Child2(Parent):
pass
print Parent.x, Child1.x, Child2.x
Child1.x = 2
print Parent.x, Child1.x, Child2.x
Parent.x = 3
print Parent.x, Child1.x, Child2.x
```









9.下面的代码会不会报错

```python
list = ['a', 'b', 'c', 'd', 'e']
print list[10:]
```







10.说出下面list1,list2,list3的输出值

```python
def extendList(val, list=[]):
    list.append(val)
    return list
list1 = extendList(10)
list2 = extendList(123,[])
list3 = extendList('a')
print "list1 = %s" % list1
print "list2 = %s" % list2
print "list3 = %s" % list3
```







11.写出你认为最Pythonic的代码













12.写出一段python代码实现一个删除一个list 里面重复元素,并保证原有序列。
如：list_element = ['a','c,','z','x','a'] 









13.python中 if __name__ == '__main__': 的作用是什么呢?

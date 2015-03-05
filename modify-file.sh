#/bin/bash

#使用find,grep sed工具
#查找文件内容中的字符串，并替换成其他字符串
#多种实现方式，主要用find grep sed 工具。
find ./ -print -exec grep -n "查找的字符串" '{}' \; -exec sed -i 's/查找到的字符串/替换成的字符串/g' {} \; 

#使用find sed工具
#这种写法简单不做任何的匹配操作 不管有没有直接使用sed去修改。
find . -name '*.php' -print | xargs sed -i 's/site_url/base_url/g'

#使用find grep工具
#查找文件内容,grep -n 显示行号
find ./ -print -exec grep -n "z" '{}' \;
find . -type f -name '*.log' -print | xargs grep -n 'z'

#使用grep工具，以正则匹配文件内容
#去掉文件中以#开头的内容，查看配置文件相当有用
grep -Ev "^#" 1.log

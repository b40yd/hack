## Usage Gperf Tools
生成完美hash函数工具。更多可以[参考](http://www.open-open.com/lib/view/open1403572223295.html)
```
gperf -C -p -j1 -i 1 -g -o -t -N sh_reserved_word  -L ANSI-C keyword > lex.c
```

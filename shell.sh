# 以时间排序文件
```
find . -type f -exec stat --format '%Y :%y %n' "{}" \; | grep -v cache | sort -nr | cut -d: -f2- | head
```

#基于时间排序
```
find . -type f -name "*.c" | xargs stat --format "%y %n" |sort -rn |head
```

# 以时间排序文件
find . -type f -exec stat --format '%Y :%y %n' "{}" \; | grep -v cache | sort -nr | cut -d: -f2- | head

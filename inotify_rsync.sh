#!/bin/bash

#echo `cat rsyncd.secrets | grep -Ev "^#|^$"`
#local files or directory.
SRC=/var/www/;
#server
DST=wackonline@127.0.0.1:backup;
#inotifywait need to rule out files or directory.
INOTIFY_EXCLUDE=""; #/var/www/backup
#inotify-tools's inotifywait command-line.
BIN=/var/www/inotify/bin/inotifywait;
#filter file or directory. 
RSYNC_EXCLUDE="";
#filter more files or directory.
RSYNC_EXCLUDE_FROM="";
file_nums=$(echo `date +%Y-%m-%d-%s`);
LOG=/var/www/log
RSYNC_LOG=$LOG/rsync-$file_nums.log;

EXCLUDE="";
if [ "$INOTIFY_EXCLUDE"x != ""x ];then
	EXCLUDE="--exclude=$INOTIFY_EXCLUDE";
fi 

rm -rf $LOG/*.log;

$BIN -mrq $EXCLUDE -e modify,delete,create,attrib,move $SRC | while read file event;do
	#If need to rule out some files,need set RSYNC_EXCLUDE variable,this variable cannot set an absolute path
	#e.g:
	#   rsync /var/www #out-sync the caches directory,need filter caches
	#   RSYNC_EXCLUDE="caches/*" 	============ is ok.
	#   RSYNC_EXCLUDE="/caches/*" 	============ is no filter caches.
	#if need to rule out more files and directory.Suggest setting RSYNC_EXCLUDE_FROM variable,this variable must be set an absolute path
	#e.g:
	#   rsync /var/www  #out-sync caches,tmp,test files or directory.
        #   RSYNC_EXCLUDE="/rsync_filter.txt"	===========	is ok.
	#cat rsync_fileter.txt:
	#	caches/*
	#	tmp/*
	#	test/* 

	if [ "$RSYNC_EXCLUDE"x == ""x ];then
		if [ "$RSYNC_EXCLUDE_FROM"x == ""x ];then
			#echo "$RSYNC_EXCLUDE_FROM ....from";
			rsync -avrhz --progress --delete $SRC $DST > $RSYNC_LOG;
		else
			#echo "ALL NULL.";
			rsync -avrhz --progress --delete --exclude-from="$RSYNC_EXCLUDE_FROM" $SRC $DST > $RSYNC_LOG;
		fi
	else
		#echo "$RSYNC_EXCLUDE ...";
		#####echo "rsync -avrhqzt --progress --delete --exclude \"$RSYNC_EXCLUDE\" $SRC $DST";
		rsync -avrhz --progress --delete --exclude "$RSYNC_EXCLUDE" $SRC $DST > $RSYNC_LOG;
	fi

	#echo "${file} was rsynced,status: ${event}";
done

#!/bin/bash

pid=`pidof java`
if [ $? -eq 0 ];then
	kill -9 $pid
else
	p=`ps -ef | grep java`
	#echo $p | cut -d " " -f2 
	pid=`echo $p |awk -F ' ' '{print $2}'`
	kill -9 $pid
fi

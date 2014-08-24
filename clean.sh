#! /bin/sh

self_pid=$$
for pid in `ps -ef |grep -i mmplay|awk '{print $2}'`
do
	if [ ${self_pid} -gt ${pid} ];
	then
		echo $pid
		kill $pid
	fi
done
num=`ps -ef |grep -i gst_play|awk '{print $2}'`
kill $num
ipcrm -M 0x703384e

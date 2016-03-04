#!/bin/bash
## send data from camera to Client
## @author tim
## @version 1.0
## @date : March 2nd 2016
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:usr/local/sbin:~/bin
export PATH


workpath="/home/monk/Workspace/opencv/getPicFromCamera/data/"
cd $workpath
flag=`ls | grep "file" -v`
declare -i recentFile 
recentFile=0
while [ "$flag" == "" ]
	do
		flag=`ls | grep "file" -v`
	done
echo "have flag"
declare -i flag
while [ 1 == 1 ]
	do
		flag=`ls | grep "file" -v`
		if [ "$recentFile" -lt "$flag" ];
		then
			recentFile=$(($recentFile+1))
			fileName=`printf "file%06d.jpg" $recentFile `
			mv $fileName ../data2/
		##	sz $fileName 
		##	rm $fileName -rf
		fi
	done

#!/bin/bash
#备份我的emacs配置
#还有一点小问题：不能去掉备份后的前缀

if [ $# != 1 ];then
    echo "usage ./backup_emacs.sh where-you-want-to-backup"
    exit 1
fi 
DATE=`date +%y_%m_%d`
NAME=$1emacs_${DATE}.tar.bz2
echo "I will backup your emacs configure file to $NAME"

echo "Is that right?"
echo "yes or no"

read TMP

CONDITION="no"

while [ "$CONDITION" == "no" ]; do

case "$TMP" in
    yes | Yes | y | Y) echo "yes"
	echo "I will begin backup"
	# tar -jcvf $NAME ~/.emacs.d ~/.emacs ~/.emacs.bmk --transform "s/home\/pengpengxp/./g"
	tar -jcvf $NAME ~/.emacs.d ~/.emacs ~/.emacs.bmk --transform "s/home\/pengpengxp/./g"
	CONDITION="yes"
	;;
    n* | N*) echo "no"
	exit 1
	;;
    *) echo "usage ./backup_emacs.sh where-you-want-to-backup"
	exit 1
	;;
esac
done

echo "end"

exit 0

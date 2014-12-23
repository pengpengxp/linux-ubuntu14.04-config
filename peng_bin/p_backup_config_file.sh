#!/bin/bash
# backup my config file
# 2014年 07月 19日 星期六 11:42:12 CST
# not finished:need to choose which file to be backup

cd /home/pengpengxp/
# the file need to be backup
FILE="/home/pengpengxp/.bashrc \
/home/pengpengxp/.vimrc \
/home/pengpengxp/.fluxbox \
/home/pengpengxp/peng_bin \
/home/pengpengxp/.vimperatorrc \
/home/pengpengxp/change_key_binding \
/home/pengpengxp/blog_peng";

if [ $# != 1 ];then
    echo "usage ./backup_emacs.sh where-you-want-to-backup"
    exit 1
fi 

DATE=`date +%y_%m_%d`
NAME=$1config_${DATE}.tar.bz2
echo "I will backup configure file to $NAME"
echo "Is that right?"
echo "yes or no"

read TMP
CONDITION="no"

while [ "$CONDITION" == "no" ]; do

case "$TMP" in
    yes | Yes | y | Y) echo "yes"
	echo "I will begin backup"
	CONDITION="yes"
	tar -cvf $NAME $FILE
	;;
    n* | N*) echo "no"
	exit 1
	;;
    *) echo "usage ./backup_emacs.sh where-you-want-to-backup"
	exit 1
	;;
esac
done
echo "Success"
exit 0

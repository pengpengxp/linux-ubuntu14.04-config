#!/bin/bash
# sum the total size of files fount by the command in the specific directory
# 2014年 07月 20日 星期日 15:36:08 CST

# !!!UNFINISHED:need to pass the comamnd as argument to this script
# !!!should be use as:p_sum_directory /directory/to/calculate command

if [ $# -ne 1 ]
then
    echo usage "p_sum_directory.sh /directory/to/calculate";
    exit 1;
fi

cd $1;
COMMAND=$2;
count=0;
for i in `ls|grep -v pdf`
do
    # echo $i;
    temp=`du -s -B1 $i 2>&1|grep -v du|awk '{print $1}'`;
    if [ "$temp" != "" ]
    then
	count=`expr $count + $temp`;
    fi
done
echo `expr $count / 1024 / 1024` MB;
exit 0


exit 0

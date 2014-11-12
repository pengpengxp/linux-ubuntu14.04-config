#!/bin/bash
# find my config file need to be backup

cd ~;
for i in `find ~ -maxdepth 1`
do
    temp=`basename $i|grep -E '^\..*$'`;
    # temp=`basename $i|grep -E '^\..*$'|grep -i -v emacs`;
    if [ "$temp" != "" ]
    then
	echo $temp;
    fi
done
exit 0

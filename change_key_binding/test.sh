#!/bin/bash

key_result=`xmodmap | grep lock |gawk '{x = $2;y = tolower(x);print y}'`

if [ $key_result = "caps_lock" ]
then
	echo "YES"
else
	echo "NO"
fi
exit 0

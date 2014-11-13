#!/bin/bash 

# generate my word list from the sdcv_history file make the word uniq,
# sort the word and delete the chinese charactor.

# Writen by pengpengxp(pengpengxppri@gmail.com)

cd ~;

#I only need to remember a little `long' word.
cat .sdcv_history|sort -n|uniq|sed '/[^-a-zA-Z _.]/ d'|egrep -i '[-a-z _.]{6,20}'


exit 0;


# what need to do

# make the output more beautiful and convert them to pdf for printing
# out.

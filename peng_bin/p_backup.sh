# p_backup.sh --- 
# 
# Filename: p_backup.sh

# Description: backup my files backup my files. This is not a perfect
# one.

# Author: pengpengxp
# Email: pengpengxppri@gmail.com
# Created: 四 12月 25 20:43:44 2014 (+0800)
# Version: 
# Last-Updated: 二 12月 30 20:56:24 2014 (+0800)
# 
# 
# TODO: give some argument to this script to some specifical function.
# 

# Code:


#!/bin/bash


# where you want to backup
DST="/media/pengpengxp/Linux/pengpengxp/"
echo "################################################################"
echo "I'll backup the file to $DST"

# change the directory to $HOME
echo "################################################################"
echo "change the directory to $HOME"
cd $HOME

# the arguments send to rsync
echo "if you want to show the details?"
read TEMP
if [ "$TEMP" = "yes" ]
then
    ARGU=" -av --progress --stats "
else
    ARGU=" -av "
fi

################################################################
#### check whether the disk is mounted or not.
################################################################
echo "################################################################"
echo "I'll check the backup disk first."

if [ -d $DST ]
then
    echo "yes, the backup disk is mounted successfully."
else
    echo "no,Please mount the backup disk first sir..."
    exit 0
fi
################################################################

echo "################################################################"
echo "different user backup different files."

if [ "`/usr/bin/id -u`" != "0" ]
then
    echo "I'm $USER, and I 'll only backup my home directory $HOME."
    echo "Is that right? You MUST type yes to accept it!!!"
    read TEMP
    if [ $TEMP = "yes" ]
    then
	echo "yes,I'll do the backup."
	rsync $ARGU .bash_history $DST
	rsync $ARGU .bash_logout $DST
	rsync $ARGU .bashrc $DST
	rsync $ARGU bin $DST
	rsync $ARGU blog_peng $DST
	rsync $ARGU Calibre_Book $DST
	rsync $ARGU change_key_binding $DST
	rsync $ARGU .config $DST
	rsync $ARGU data $DST
	rsync $ARGU .dropbox $DST
	rsync $ARGU Dropbox $DST
	rsync $ARGU .dropbox-dist $DST
	rsync $ARGU .emacs $DST
	rsync $ARGU .emacs.bmk $DST
	rsync $ARGU .emacs.d $DST
	rsync $ARGU .fluxbox $DST
	rsync $ARGU .fvwm $DST
	rsync $ARGU .fvwm-crystal $DST
	rsync $ARGU .git $DST
	rsync $ARGU .gitconfig $DST
	rsync $ARGU .gitignore $DST
	rsync $ARGU gtd $DST
	rsync $ARGU .i3 $DST
	rsync $ARGU myconfig_backup $DST
	rsync $ARGU netp $DST
	rsync $ARGU notes $DST
	rsync $ARGU .oh-my-zsh $DST
	rsync $ARGU org $DST
	rsync $ARGU peng_bin $DST
	rsync $ARGU qq_document $DST
	rsync $ARGU src $DST
	rsync $ARGU temp $DST
	rsync $ARGU .vim $DST
	rsync $ARGU .viminfo $DST
	rsync $ARGU .vimperator $DST
	rsync $ARGU .vimperatorrc $DST
	rsync $ARGU .vimrc $DST
	rsync $ARGU VirtualBox $DST
	rsync $ARGU VMs $DST
	rsync $ARGU vmware $DST
	rsync $ARGU .wine $DST
	rsync $ARGU workshop $DST
	rsync $ARGU xiepeng_learn $DST
	rsync $ARGU .xine $DST
	rsync $ARGU .xinputrc $DST
	rsync $ARGU .Xmodmap $DST
	rsync $ARGU .zshrc $DST
	rsync $ARGU 视频 $DST
	rsync $ARGU 图片 $DST
	rsync $ARGU 文档 $DST
	rsync $ARGU 下载 $DST
	rsync $ARGU 音乐 $DST
	exit 0;
    else
	echo "You didn't accept it!!! Exit now..."
	exit 0;
    fi
else
    echo "I'm root, I'll only backup the /etc and /usr directory."
    echo "Is that right? You MUST type yes to accept it!!!"
    read TEMP
    if [ $TEMP = "yes" ]
    then
	rsync $ARGU /etc $DST
	rsync $ARGU /usr $DST
	exit 0;
    else
	echo "You didn't accept it!!! Exit now..."
	exit 0;
    fi

fi

# p_backup.sh ends here

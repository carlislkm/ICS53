#!/bin/bash

#echo -n "enter filename->"
#read mycomm

mycomm=$1

IFS=":"

for i in $PATH
do
   if [ -f "${i}/$mycomm" ];then
      echo ${i}/$mycomm
      exit 0
   fi
done

   echo "'$mycomm' not found!"

exit 1

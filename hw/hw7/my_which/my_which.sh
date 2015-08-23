#!/bin/bash

IFS=":"
x=false

for i in $*
do
	for j in $PATH
	do
		if [ -x "${j}/$i" ];then
			echo $j/$i
			x=true
			break 
		fi
	done
	if [ $x == false ]; then
		echo my_which $i not found in --$PATH--
		
	fi
	x=false
	
done

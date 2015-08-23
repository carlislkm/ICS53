#!/bin/bash


for i in $*
do

num_subdir=-1
num_files=0
empty_files=0
echo
echo DIRCHECK: $i
	for j in `find $i` 
	do
		if [ -d "$j" ]
		then
			num_subdir=`expr $num_subdir + 1`	
		
		fi
		if [ -f "$j" ]
		then
			num_files=`expr $num_files + 1`
		fi

		if [ ! -s "$j" ] && [ -f "$j" ]		
		then
			empty_files=`expr $empty_files + 1`
			echo $j

		fi

	done
	echo	
	echo NUMBER OF DIRS:  $num_subdir 
	echo NUMBER OF FILES: $num_files 
	echo NUMBER OF EMPTY FILES: $empty_files
	size=$(du -sh $i)
	echo SIZE OF DIR: $size
	echo 


done

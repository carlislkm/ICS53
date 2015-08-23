#!/bin/bash

options=$@
path=$1
args=($options)
i=0

filearray=(`tree $path -if`)
name=
ftype=
execa=
results=


for argument in $options
	do 
		i=$(( $i + 1))
	
		case $argument in
			-name) 
				#echo "NAME-> ${args[$i]}"
				name=${args[$i]}
				 ;;
				
			-type) 
				#echo "TYPE-> ${args[$i]}"
				ftype=${args[$i]}
			         ;;
			#-print) echo "PRINT" ;;
			-exec) 
				#echo "SIZE OF ARRAY ${#args[@]} -----"
				#c=`expr ${#args[@]} - ${args[$i-1]}`
				#echo "THIS IS $c HERE"
				#echo "EXEC-> ${args[$i]} ${args[$i+1]} ${args[$i+2]}"
				 ;;

			\?) #echo "ELSE";;
		esac
	done

for item in ${filearray[*]}
	do
		
		#if [ ! -z "$ftype" ] && [ -$ftype "$item" ]
		if [ ! -z "$ftype" ]
		then
			if [ -$ftype "$item" ]
			then #FTYPE
				if [ ! -z "$name" ]
				then #FTYPE && NAME
					f="${item##*.}"
					t="${name##*.}"
					#echo "**-${f}-**$t--**"
					if [[ $t == $f ]]
					then
						results+=($item)
					fi
				else #FTYPE && NOT NAME
					#other stuff
					
					results+=($item)
					#echo "FTYPE && NOT NAME"
				fi
			fi	
		else #NOT FTYPE
			if [ ! -z "$name" ]
			then #NOT FTYPE && NAME 
				#echo "NOT FTYPE && NAME"
				f="${item##*.}"
				t="${name##*.}"
			
				if [[ $t == $f ]]
				then
					results+=($item)
		
			
				fi	
			else #Not FTYPE & NOT NAME
				results+=($item)
				#echo "NOT FTYPE && NAME"

			fi
		fi
		

	done
echo
echo "DIR:  $path"
echo
echo

for res in ${results[*]}
	do
		echo "--> $res"

	done

echo 
echo






 

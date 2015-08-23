#!/bin/bash

while getopts ":a:name:" opt;do
	case $opt in
		a)
			echo "-a PARAMETER: $OPTARG " >&2
			;;
		name)
			echo "-name PARAMETER: $OPTARG " >&2
			;;
		\?)
			echo "invalid option: -$OPTARG " >&2
			;;

		:)
			echo "OPTION -$OPTARG requires an argument" >&2
			exit 1
			;;
	esac
done

	


#!/bin/sh

if [ "$#" -ne 2 ]; then
	echo "ERROR: Invalid parameter !"
	echo "Usage:"
	echo "      generateData.sh [NumberData] [NumberFile] "
	echo ""
	echo "Ex:   generateData.sh 500 5  # will generate 500 data in 5 files"  
else
	if [ "$1" -eq "$1" ]; then
		if [ "$2" -eq "$2" ]; then
			file=0
			while [ $file -lt $2 ]; do
				./dataGenerator.py > input$file.dat
				data=1
				while [ $data -lt $1 ]; do
				
					./dataGenerator.py >> input$file.dat
					data=$(($data+1))
				done
				file=$(($file+1))
			done
		fi
	fi
fi

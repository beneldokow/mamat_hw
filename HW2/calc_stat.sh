#!/bin/bash

if [ $# != 1 ]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

file_name="$1.txt"

if [ ! -e "$file_name" ]; then
    echo "Course not found" >&2
    exit 1
fi

dir_name="$1_stat"

if [ -d "$dir_name" ]; then
    rm -rf $dir_name
fi

mkdir $dir_name

./hist.exe "$file_name" > "$dir_name/histogram.txt" 

./mean.exe < "$file_name" > "$dir_name/statistics.txt"


grades_hist=$(./hist.exe "$file_name" "100") 
grades_num=$(cat "$file_name" | wc -l)

echo "$grades_hist" | ./median.exe "-" "$grades_num" >> "$dir_name/statistics.txt"
./min.exe "$file_name" >> "$dir_name/statistics.txt"
./max.exe "$file_name" >> "$dir_name/statistics.txt"

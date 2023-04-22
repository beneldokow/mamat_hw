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

echo -ne "$(./mean.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./median.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./min.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./max.exe "$file_name")\t" >> "$dir_name/statistics.txt"

sum_all=$(./hist.exe "$file_name" -n_bins 100 | awk '{s+=$NF} END {print s}')
sum_pass=$(./hist.exe "$file_name" -n_bins 100 | tail -n 45 | awk '{ sum += $NF } END { print sum }')
percentage=$(($sum_pass * 100 / $sum_all))

echo -e "$percentage%\t" >> "$dir_name/statistics.txt"
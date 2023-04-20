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
./median.exe "$file_name" >> "$dir_name/statistics.txt"
./min.exe "$file_name" >> "$dir_name/statistics.txt"
./max.exe "$file_name" >> "$dir_name/statistics.txt"

mapfile -t grades < ./hist.exe "$file_name" "100"

count_pass=0
count_all=0

for grade in "${grades[@]}"; do
    this_grade=$(echo "$grade" | awk '{ if ($2 ~ /^[0-9]+$/) print $2 }')
    if (( this_grade > 55 )); then
       (( count_pass++ ))
     fi
    ((count_all++))
done

#echo $count_pass//$count_all >> "$dir_name/statistics.txt"
percent=$(awk "BEGIN {printf \"%.2f\", $count_pass/$count_all * 100}")

echo -e "55.00\t$count_pass\t$count_all\t100\t$percent%" >> "$dir_name/statistics.txt"
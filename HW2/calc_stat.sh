#!/bin/bash

# Check if the number of arguments provided is exactly one
if [ $# != 1 ]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

file_name="$1.txt"

# Check if the input file exists
if [ ! -e "$file_name" ]; then
    echo "Course not found" >&2
    exit 1
fi

dir_name="$1_stat"

# If the output directory already exists, remove it
if [ -d "$dir_name" ]; then
    rm -rf $dir_name
fi

mkdir $dir_name

# Generate the histogram and save it to the histogram file in the output directory
./hist.exe "$file_name" > "$dir_name/histogram.txt" 

# Compute the mean, median, minimum, and maximum grades,
# and append them to the statistics file in the output directory
echo -ne "$(./mean.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./median.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./min.exe "$file_name")\t" >> "$dir_name/statistics.txt"
echo -ne "$(./max.exe "$file_name")\t" >> "$dir_name/statistics.txt"

# Compute the percentage of students who passed the course 
# and append it to the statistics file in the output directory
sum_all=$(./hist.exe "$file_name" -n_bins 100 | awk '{s+=$NF} END {print s}')
sum_pass=$(./hist.exe "$file_name" -n_bins 100 | tail -n 45 |\
awk '{ sum += $NF } END { print sum }')
percentage=$(($sum_pass * 100 / $sum_all))
echo -e "$percentage%\t" >> "$dir_name/statistics.txt"
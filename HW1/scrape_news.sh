#!/bin/bash

#getting data from main website
articles=$(wget --no-check-certificate -O - \
https://www.ynetnews.com/category/3082 2>/dev/null |\
    grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+")

#counting urls
list=$(echo "$articles"| tr '\n' '\0' | sort -uz | tr '\0' '\n')
echo $(echo "$list" | wc -l) > results.csv

#going through urls
for url in $list; do
    echo -n "$url, " >> results.csv
    data=$(wget --no-check-certificate -O - $url 2>/dev/null)
    count=0
    
    #checking if no name shows
    for name in Netanyahu Gantz Bennett Peretz; do
        count+=$(echo "$data" | grep -o "$name" | wc -l)
    done
    
    #if no name shows printing -
    if [ $count -eq 0 ]; then
        echo "-" >> results.csv
    
    #otherwise appending to results with the given assignment format
    else
        for name in Netanyahu Gantz Bennett Peretz; do
            num=$(echo "$data" | grep -o "$name" | wc -l)
            if [ $name = "Peretz" ]; then
                echo "$name, $num" >> results.csv
            else
                echo -n "$name, $num, " >> results.csv
            fi
        done
    fi

done

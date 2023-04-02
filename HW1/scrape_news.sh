#!/bin/bash

articles=$(wget --no-check-certificate -O - \
https://www.ynetnews.com/category/3082 2>/dev/null |\
    grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+")


list=$(echo "$articles"| tr '\n' '\0' | sort -uz | tr '\0' '\n')
echo $(echo "$list" | wc -l)
echo

for url in $list; do
    echo -n "$url, "
    count=0
    
    for name in Netanyahu Gantz Bennett Peretz; do
        data=$(wget --no-check-certificate -O - $url 2>/dev/null)
        count+=$(echo "$data" | grep -c $name)
    done
    
    if [ $count -eq 0 ]; then
        echo "-"
    else
        for name in Netanyahu Gantz Bennett Peretz; do
            data=$(wget --no-check-certificate -O - $url 2>/dev/null)
            echo -n "$name, "
            num=$(echo "$data" | grep -c $name)
            if [ $name = "Peretz" ]; then
                echo "$num"
            else
                echo -n "$num, "
            fi
        done
    fi
    echo
done
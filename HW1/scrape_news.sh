#!/bin/bash

articles=$(wget --no-check-certificate -O - \
https://www.ynetnews.com/category/3082 2>/dev/null |\
    grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+")


list=$(echo "$articles"| tr '\n' '\0' | sort -uz | tr '\0' '\n')
echo $(echo "$list" | wc -l)

for url in $list; do
    echo -n "$url, "
    for name in Netanyahu Gantz Bennett; do
        data=$(wget --no-check-certificate -O - $url 2>/dev/null)  
        echo -n "$name, "
        echo "$data" | grep -c $name | tr -d '\n'
        echo -n ", "
    done
    name=Peretz
    data=$(wget --no-check-certificate -O - $url 2>/dev/null)
        echo -n "$name, "
        echo "$data" | grep -c $name
        echo
done
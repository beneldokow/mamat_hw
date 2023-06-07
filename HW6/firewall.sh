#!/bin/bash

# Read all packets from input, removing spaces and tabs
packets=$(cat | tr -s ' ')

# Initialize variable for storing good packets
succesful=""

# Read each line from the input file
while read line; do
    # Remove spaces and comments from the line
    line=$(echo $line | tr -d ' ' | sed -e 's/#.*//')

    # Skip empty lines
    if [ ! -z "$line" ]; then
        # Assign all packets to the remaining packets variable
        remained=$packets

        # Split the line into four parts and process each part
        for index in {1..4}; do
            rule=$(echo $line | cut -d "," -f$index)
            remained=$(echo "$remained" | ./firewall.exe "$rule")
        done

        # Append the remaining packets to the good packets list
        succesful+=$(echo "$remained")
        succesful+="\n"
    fi
done < "$1" # Read lines from the input file specified as argument

# Print the good packets in sorted order, without empty lines or spaces
echo -e "$succesful" | grep -vE ^$ | tr -d ' ' | sort | uniq

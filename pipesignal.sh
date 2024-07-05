#!/bin/bash

# Example commands
# < /dev/urandom cat | head -n 5 > temp_out 

< input_tc grep "Now" | wc -w > not-existing/test.txt

statuses=("${PIPESTATUS[@]}")

for i in "${!statuses[@]}"; do
    status=${statuses[$i]}
    if (( status >= 128 )); then
        signal=$((status - 128))
        echo "Command $((i+1)) terminated by signal: $signal"
    else
        echo "Command $((i+1)) exited with status: $status"
    fi
done
#!/bin/bash

echo "Top 5 Memory-Consuming Processes"
echo "--------------------------------"
ps -eo pid,comm,%mem --sort=-%mem | head -n 6

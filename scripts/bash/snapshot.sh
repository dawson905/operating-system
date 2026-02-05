#!/bin/bash
echo "System Health Report"
echo "--------------------"
echo "Date and Time: $(date)"
echo "Hostname: $(hostname)"
echo "Current User: $(whoami)"
echo
echo "Disk Usage (Root /):"
df -h /

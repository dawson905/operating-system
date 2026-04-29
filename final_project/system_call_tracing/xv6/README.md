# System Call Tracing in xv6

# Group 7
Dawson Westnedge 
Luke Marting 
Jacob Weigel

# Project Overview

This project adds a custom system call tracing feature to xv6. The system can display selected system calls during runtime along with process ID and return values

# Files Modified

- proc.h
- proc.c
- syscall.h
- syscall.c
- sysproc.c
- trace.c

# How to Compile

```bash
make clean
make

# How to run
make qemu-nox

#Inside Xv6 file
trace

# Expected Result
The trace program prints selected system calls such as write, open, read, and close while the program runs

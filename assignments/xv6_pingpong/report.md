For this assignment and question 19 I wrote a C program that creates two pipes and then forks into a parent and child process. One pipe is used for communication from the parent to the child, and the other pipe is used for communication from the child back to the parent. The goal was to pass a single byte back and forth repeatedly and measure how fast it can happen.

After calling fork(), each process closes the pipe ends it does not use. The parent sends one byte to the child. The child reads that byte and immediately writes it back. The parent then reads it back. That full round trip counts as one exchange. This loop runs for a large number of exchanges so the timing is more accurate.

To measure performance, I recorded the time right before the exchange loop starts and again after it finishes. I then divided the total number of exchanges by the elapsed time to calculate exchanges per second.

Results:

E= 1000000_
ET = 3.314307 seconds
Rate = 301722.21 E/s

The rate ended up being very high since only one byte is being transferred each time, but the overhead from system calls and context switching between processes is still noticeable. Running more exchanges made the timing more consistent.

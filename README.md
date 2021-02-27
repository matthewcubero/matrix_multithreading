# matrix_multithreading
Name: Matthew Cubero
Student ID: 9301499796
email: macubero@usc.edu

Summary: A program that uses 10 threads assigned to each element of a 1x5 matrix and a 5x1 matrix. 5 of the threads forward their values to the corresponding threads via pipe. The receiving pipe is responsible for executing the multiplication and adding to the overall sum.

References:
https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html
To find parameters on write and read I used this website. The read and write functions are seen in all the thread functions I've created.

https://www.geeksforgeeks.org/pipe-system-call/
I used this website to correctly and properly use pipe as well as error checking within the pipes as seen in lines 105-125 in matrix.cpp.

https://linuxprograms.wordpress.com/2008/01/23/piping-in-threads/
Structured my code similar to this website's example with file descriptors instantiated globally, creating all threads next to each other (not using a for loop), and joining the threads right after creation.

https://en.cppreference.com/w/c/chrono/clock_t
Used this website for timing the speed of my program. Lines 10, 200, and 201 were from this site.
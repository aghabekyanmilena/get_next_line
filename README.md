# get_next_line

## Overview
get_next_line is a custom implementation of a function that reads a line from a file descriptor, one call at a time.
This function efficiently handles buffered reading and retains any leftover databetween calls, making it useful for reading from files, standard input, and other stream-based sources.

## Features
- Reads a file line by line.
- Efficient handling of buffer management.
- Works with any file descriptor.
- Supports multiple file descriptors (bonus part).
- No memory leaks and optimized performance.

## Functions
1. set_line

This function extracts the remaining part of the buffer after a newline (\n) andensures that line_buffer only contains a single line.
2. fill_line

This function reads from the file descriptor into a buffer and appends it to theexisting string (left) until it finds a newline (\n) or reaches the end of the file.
3. get_next_line

This function orchestrates reading and processing a line from the file descriptor.

## Testers
https://github.com/Tripouille/gnlTester 

https://github.com/kodpe/gnl-station-tester

## Return Values
A string containing the next line (including the newline `\n` if present).
`NULL` when end-of-file (EOF) is reached or an error occurs.

## Error Handling:
Returns `NULL` if memory allocation fails or an invalid file descriptor is given

## Bonus Features
The bonus version of `get_next_line` supports multiple file descriptors, meaningyou can read from multiple files simultaneously without mixing data.


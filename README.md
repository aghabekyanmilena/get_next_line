1. set_line(char *line_buffer)
Purpose:

This function extracts the portion of the string after the first newline (\n).
It also modifies line_buffer to ensure that it ends at the first newline.
Step-by-step explanation:

Find the position of the first newline (\n) or the null terminator (\0).
The loop runs through line_buffer until it finds \n or \0.
If there is no newline (\n), return NULL.
This means the entire buffer has been processed.
Extract the part of the string after the newline.
ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i) creates a new string that contains everything after the newline.
Set the character after the newline to \0 to terminate the first part of the string.
This ensures that line_buffer only contains the current line.
Return the remaining part of the buffer.
This is stored in left for future calls to get_next_line.

2. fill_line(int fd, char *left, char *buffer)
Purpose:

This function reads the file chunk by chunk and joins the contents together until a newline (\n) is found.
Step-by-step explanation:

Initialize read_bytes to 1 to enter the loop.
Read BUFFER_SIZE bytes from the file into buffer.
read(fd, buffer, BUFFER_SIZE) reads up to BUFFER_SIZE characters from the file.
If read() fails, free memory and return NULL.
This happens when read() returns -1.
If read_bytes == 0, stop reading.
This means we have reached the end of the file.
Null-terminate buffer at the end of the data read.
Join the newly read data to the existing left string.
ft_strjoin(tmp, buffer) appends buffer to left.
If a newline (\n) is found in buffer, stop reading.
We only need to read enough to complete one line.

3. get_next_line(int fd)
Purpose:

This is the main function that returns one line at a time from the file descriptor (fd).
Step-by-step explanation:

Check if the file descriptor (fd) is valid.
If fd < 0, return NULL.
Allocate memory for the buffer that will store data read from the file.
Call fill_line() to read the next line from the file.
This function reads data and appends it to left.
Free the buffer after reading.
Extract the next line from the buffer using set_line().
set_line() splits the buffer into the current line and the remaining part.
Return the extracted line.

Helper Functions:

4. ft_strlen(const char *src)
Purpose:

Counts the number of characters in a string until the null terminator (\0).
Step-by-step explanation:

If src is NULL, return 0.
Use a loop to count characters until \0.

5. ft_strdup(char *str)
Purpose:

Creates a duplicate of a given string.
Step-by-step explanation:

Allocate memory for a new string of the same length.
Copy characters one by one.
Return the new copy.

6. ft_strjoin(char *s1, char *s2)
Purpose:

Joins two strings together into a new allocated string.
Step-by-step explanation:

Compute the total length of s1 and s2.
Allocate memory for the new string.
Copy s1 into the new string.
Append s2 to it.
Free the old s1 to prevent memory leaks.
Return the new string.

7. ft_strchr(const char *str, int c)
Purpose:

Finds the first occurrence of a character c in str.
Step-by-step explanation:

Loop through str until c is found or the string ends.
Return the address of c if found, otherwise return NULL.

8. ft_substr(char const *s, unsigned int start, size_t len)
Purpose:

Extracts a substring from a string starting at start for len characters.
Step-by-step explanation:

If s is NULL, return NULL.
Check if start is beyond the length of s. If so, return an empty string.
If len is greater than the remaining string length, adjust it.
Allocate memory for the substring.
Copy characters from s[start] to s[start + len].
Return the new substring.
How It Works Together
get_next_line(fd) calls fill_line(fd, left, buffer).
fill_line() reads the file chunk by chunk and appends to left.
Once a newline (\n) is found, fill_line() returns the full line.
get_next_line() then calls set_line() to extract the remaining part of left for the next call.
get_next_line() returns the extracted line.
This cycle repeats until the entire file is read.

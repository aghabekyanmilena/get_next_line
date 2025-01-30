This code implements a `get_next_line` function that reads a file descriptor line by line, handling newline characters and buffering. Let’s go through it **line by line**, function by function.

---

## **1. `set_line` function**
This function extracts the remaining part of the buffer after a newline (`\n`) and ensures that `line_buffer` only contains a single line.

```c
static char	*set_line(char *line_buffer)
```
- Declares a static function `set_line` that takes a `char *line_buffer` and returns a `char *`.  
- The function is **static**, meaning it is only accessible within the file where it is defined.

```c
char	*left;
ssize_t	i;
```
- Declares `left` (which will store the remaining part of the buffer after `\n`) and `i` (used as an index).

```c
if (!line_buffer)
	return (NULL);
```
- If `line_buffer` is `NULL`, return `NULL` immediately.

```c
i = 0;
while (line_buffer[i] && line_buffer[i] != '\n' && line_buffer[i] != '\0')
	i++;
```
- Iterates over `line_buffer` until it reaches a newline (`\n`) or the end of the string (`\0`).

```c
if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
	return (NULL);
```
- If the newline was **not found**, or if it is **at the end of the buffer**, there is no remaining text, so return `NULL`.

```c
left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
```
- Calls `ft_substr` to extract everything **after** `\n` into `left`.

```c
if (!left)
	return (NULL);
```
- If `ft_substr` fails (e.g., memory allocation fails), return `NULL`.

```c
line_buffer[i + 1] = '\0';
```
- Truncates `line_buffer` at `i + 1`, ensuring it only contains the first line.

```c
if (*left == '\0')
	left = NULL;
```
- If `left` is empty (e.g., no more content after `\n`), set `left` to `NULL`.

```c
return (left);
```
- Returns the remaining part of the buffer (`left`).

---

## **2. `fill_line` function**
This function reads from the file descriptor into a buffer and appends it to the existing string (`left`) until it finds a newline (`\n`) or reaches the end of the file.

```c
static char	*fill_line(int fd, char *left, char *buffer)
```
- A **static** function that reads from file descriptor `fd`, updates `left`, and returns the updated string.

```c
ssize_t	read_bytes;
char	*tmp;
```
- Declares `read_bytes` (stores the number of bytes read) and `tmp` (a temporary pointer for string joining).

```c
read_bytes = 1;
while (read_bytes > 0)
```
- Initializes `read_bytes = 1` and starts a loop to read from `fd` until EOF (read returns `0`).

```c
read_bytes = read(fd, buffer, BUFFER_SIZE);
```
- Reads up to `BUFFER_SIZE` bytes from `fd` into `buffer`.

```c
if (read_bytes == -1)
	return (NULL);
```
- If `read` fails, return `NULL`.

```c
else if (read_bytes == 0)
	break ;
```
- If `read_bytes == 0`, **EOF is reached**, so break the loop.

```c
buffer[read_bytes] = '\0';
```
- Null-terminate the buffer (since `read` does not append `\0`).

```c
tmp = left;
left = ft_strjoin(tmp, buffer);
```
- Joins `left` and `buffer` into a new string using `ft_strjoin`.

```c
if (!left)
{
	free(tmp);
	tmp = NULL;
	return (NULL);
}
```
- If `ft_strjoin` fails, free `tmp` and return `NULL`.

```c
if (ft_strchr(buffer, '\n'))
	break ;
```
- If `buffer` contains a newline (`\n`), stop reading more data.

```c
return (left);
```
- Returns the updated `left`.

---

## **3. `get_next_line` function**
This function orchestrates reading and processing a line from the file descriptor.

```c
char	*get_next_line(int fd)
```
- Main function that reads from `fd` and returns a single line.

```c
static char	*left = NULL;
```
- Declares a **static** `left` variable to keep track of leftover text between function calls.

```c
char		*line;
char		*buffer;
```
- Declares `line` (stores the final line to return) and `buffer` (temporary buffer for reading).

```c
buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
```
- Allocates memory for `buffer` (`BUFFER_SIZE + 1` to hold `\0`).

```c
if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
```
- Checks for **invalid file descriptor** (`fd < 0`), **invalid buffer size** (`BUFFER_SIZE <= 0`), or **read error** (`read(fd, 0, 0) < 0`).

```c
free(left);
free(buffer);
left = NULL;
buffer = NULL;
return (NULL);
```
- If an error occurs, **free everything** and return `NULL`.

```c
if (!buffer)
	return (NULL);
```
- If `malloc` for `buffer` fails, return `NULL`.

```c
line = fill_line(fd, left, buffer);
```
- Calls `fill_line` to read from `fd` and get a full line.

```c
free(buffer);
buffer = NULL;
```
- Frees `buffer` after reading.

```c
if (!line || *line == '\0')
```
- If `line` is `NULL` or an empty string:

```c
free(line);
return (NULL);
```
- Free `line` and return `NULL`.

```c
left = set_line(line);
```
- Calls `set_line` to extract remaining data **after** the newline.

```c
return (line);
```
- Returns the extracted **line**.

---

## **Summary**
- `get_next_line` calls `fill_line` to read the next line from the file descriptor.
- `fill_line` appends data into `left` until a newline (`\n`) is found or EOF is reached.
- `set_line` extracts the remaining text after the newline and updates `left` for future calls.
- The function is optimized to **persist between function calls** using `static char *left`.

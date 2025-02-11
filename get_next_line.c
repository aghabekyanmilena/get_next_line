/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:38:14 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/31 13:38:09 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_line(char *line_buffer)
{
	char	*left;
	ssize_t	i;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!left)
		return (NULL);
	line_buffer[i + 1] = '\0';
	if (*left == '\0')
		left = NULL;
	return (left);
}

static char	*fill_line(int fd, char *left, char *buffer)
{
	ssize_t	read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = left;
		left = ft_strjoin(tmp, buffer);
		if (!left)
		{
			free(tmp);
			tmp = NULL;
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left = NULL;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left);
		free(buffer);
		left = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_line(fd, left, buffer);
	free(buffer);
	buffer = NULL;
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	left = set_line(line);
	return (line);
}

// int main()
// {
// 	int fd = open ("get_next_line.c", O_RDONLY);
// 	for (int i = 0; i < 20; i++)
// 		printf("%s", get_next_line(fd));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:12:15 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/31 00:07:01 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_line(char *line_buffer)
{
	char	*left;
	ssize_t	i;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!left)
		return (NULL);
	line_buffer[i + 1] = '\0';
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
		{
			free(left);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = left;
		left = ft_strjoin(tmp, buffer);
		if (!left)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left[FOPEN_MAX];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
	{
		free(left[fd]);
		free(buffer);
		left[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line(fd, left[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line || *line == '\0')
	{
		// free(line);
		return (NULL);
	}
	left[fd] = set_line(line);
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	static char	*left[FOPEN_MAX];
// 	char		*line;
// 	char		*buffer;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
// 		return (NULL);
// 	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	line = fill_line(fd, left[fd], buffer);
// 	free(buffer);
// 	if (!line || *line == '\0')
// 	{
// 		free(line);
// 		free(left[fd]);
// 		left[fd] = NULL;
// 		return (NULL);
// 	}
// 	free(left[fd]);
// 	left[fd] = set_line(line);
// 	return (line);
// }

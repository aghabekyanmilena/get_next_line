/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:12:15 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/31 13:35:32 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_line(char *line_buffer)
{
	char	*left;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (0);
	left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left == 0)
	{
		free(left);
		left = NULL;
	}
	line_buffer[i + 1] = 0;
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
	static char	*left[OPEN_MAX];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= OPEN_MAX)
	{
		free(left[fd]);
		free(buffer);
		left[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_line(fd, left[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left[fd] = set_line(line);
	return (line);
}

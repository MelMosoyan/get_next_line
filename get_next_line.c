/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosoyan <mmosoyan@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:53:49 by mmosoyan          #+#    #+#             */
/*   Updated: 2024/04/20 17:06:03 by mmosoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*reader(int fd, char *buffer, char *res)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != '\0')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!res)
			res = ft_strdup("");
		temp = res;
		res = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (res);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*res;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	res = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*res == '\0')
	{
		free(res);
		res = NULL;
		return (NULL);
	}
	line[count + 1] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = reader(fd, buffer, remain);
	free(buffer);
	buffer = NULL;
	if (!line)
	{
		return (0);
	}
	remain = extract(line);
	return (line);
}

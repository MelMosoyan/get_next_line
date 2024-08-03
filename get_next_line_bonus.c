/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosoyan <mmosoyan@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:03:57 by mmosoyan          #+#    #+#             */
/*   Updated: 2024/04/20 17:25:43 by mmosoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*reader(int fd, char *buffer, char *rem)
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
		if (!rem)
			rem = ft_strdup("");
		temp = rem;
		rem = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rem);
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
	static char	*remain[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = reader(fd, buffer, remain[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
	{
		return (0);
	}
	remain[fd] = extract(line);
	return (line);
}

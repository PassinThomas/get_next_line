/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:20:28 by tpassin           #+#    #+#             */
/*   Updated: 2023/12/23 08:21:14 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_buffer(int fd, char *next_read, char *buf);
static char	*set_line(char *line_buffer);

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)(&s[i]));
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*next_read = NULL;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 1023)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = line_buffer(fd, next_read, buf);
	free(buf);
	if (!line)
		return (NULL);
	next_read = set_line(line);
	return (line);
}

static char	*line_buffer(int fd, char *next_read, char *buf)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = BUFFER_SIZE;
	while (b_read > 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
			return (free(next_read), NULL);
		if (b_read == 0)
			break ;
		buf[b_read] = '\0';
		if (!next_read)
			next_read = ft_strdup("");
		tmp = next_read;
		next_read = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (next_read);
}

static char	*set_line(char *line_buffer)
{
	char		*stash;
	ssize_t		i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0)
		return (NULL);
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (stash[0] == 0)
		return (free(stash), NULL);
	line_buffer[i + 1] = '\0';
	return (stash);
}
/*int	main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);

	char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}*/

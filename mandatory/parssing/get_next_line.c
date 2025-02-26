/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:54:39 by asayad            #+#    #+#             */
/*   Updated: 2025/02/25 03:38:32 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*line;
	int		l;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	line = malloc ((l + 1) * sizeof(char));
	if (!line)
		return (free(s1), NULL);
	line = ft_strlcpy(s1, s2, line, l);
	return (free(s1), s1 = NULL, line);
}

char	*ft_strlcpy(char *s1, char *s2, char *line, int l)
{
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(s2);
	while (++i < l - j)
		line[i] = s1[i];
	while (--j >= 0)
		line[i + j] = s2[j];
	line[l] = '\0';
	return (line);
}

char	*make_line(char *line_read)
{
	char	*nl;
	int		i;
	int		l;

	if (!line_read || !line_read[0])
		return (NULL);
	l = ft_strlen(line_read);
	i = ft_strchr(line_read, '\n');
	if (i >= 0)
	{
		nl = ft_strdup(line_read, i);
		return (nl);
	}
	else
		nl = ft_strdup(line_read, l - 1);
	return (nl);
}

char	*get_next_line(int fd)
{
	char		*buff;
	ssize_t		bytes_read;
	static char	*line_read;
	char		*line_with_nl;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (free(line_read), NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buff), free(line_read), line_read = NULL, NULL);
		buff[bytes_read] = '\0';
		line_read = ft_strjoin(line_read, buff);
		if (ft_strchr(buff, '\n') >= 0)
			break ;
	}
	line_with_nl = make_line(line_read);
	line_read = make_stash(line_read);
	return (free(buff), buff = NULL, line_with_nl);
}

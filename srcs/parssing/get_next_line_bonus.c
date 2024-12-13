/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:54:39 by asayad            #+#    #+#             */
/*   Updated: 2024/10/28 22:18:10 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line_bonus.h>

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
	return (free(s1), line);
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
	static char	*line_read[OPEN_MAX];
	char		*line_with_nl;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		line_read[fd] = ft_strjoin(line_read[fd], buff);
		if (ft_strchr(line_read[fd], '\n') >= 0)
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (free(buff), free(line_read[fd]), line_read[fd] = NULL, NULL);
	line_with_nl = make_line(line_read[fd]);
	line_read[fd] = make_stash(line_read[fd]);
	return (free(buff), buff = NULL, line_with_nl);
}

// #include <libc.h>
// int main()
// {
// 	char *line;
// 	int fd = open("get_next_line.h",O_RDONLY);
// 	int fd1 = open("get_next_line_bonus.h",O_RDONLY);
// 	int fd2 = open("TEST.txt",O_RDONLY);
// 	int fd3 = open("main.c",O_RDONLY);
// 	/*--------------------------------------*/
// 	line = get_next_line(fd);
// 		printf("----%s-----",line);
// 		free(line);
// 	/*--------------------------------------*/	
// 	line = get_next_line(fd1);
// 	printf("#########%s######",line);
// 		free(line);
// 	/*--------------------------------------*/
// 	line = get_next_line(fd2);
// 	printf("!!!!!!!%s!!!!!!!!",line);
// 		free(line);
// 	/*--------------------------------------*/
// 	line = get_next_line(fd3);
// 	printf("&&&&&&%s&&&&&&",line);
// 		free(line);
// 	//system("leaks a.out");
// 	line = get_next_line(fd);
// 		printf("----%s-----",line);
// 		free(line);
// }
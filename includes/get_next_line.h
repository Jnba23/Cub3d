/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:52:51 by asayad            #+#    #+#             */
/*   Updated: 2025/02/23 20:15:08 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*make_line(char *line_read);
char	*make_stash(char *line_read);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s, int i);
int		ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*ft_strlcpy(char *s1, char *s2, char *line, int l);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:52:51 by asayad            #+#    #+#             */
/*   Updated: 2024/01/19 19:18:35 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <libc.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:06:41 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 21:17:05 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_atoi(char **str, bool *a)
{
	int		num;
	bool	b;
	int		i;

	num = 0;
	b = false;
	skip_spaces_ptr(str);
	if (!check_sign(str))
		return (*a = true, 0);
	while (**str == '0' && ft_isdigit(*(*str + 1)))
		(*str)++;
	i = 0;
	while (**str >= 48 && **str <= 57)
	{
		b = true;
		num = (num * 10) + (**str - 48);
		if (num > 255 || i > 3)
			return (*a = true, 0);
		(*str)++;
		i++;
	}
	if (b == false)
		return (*a = true, 0);
	return (num);
}

void	skip_spaces_ptr(char **line)
{
	while ((**line >= 9 && **line <= 13) || **line == 32 || **line == ',')
		(*line)++;
}

int	check_sign(char **str)
{
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			return (0);
		(*str)++;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		if (write(fd, &s[i++], 1) == -1)
			perror("Write failed !");
	}
	if (write(fd, "\n", 1) == -1)
		perror("Write failed !");
}

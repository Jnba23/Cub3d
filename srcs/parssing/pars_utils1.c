/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:06:41 by asayad            #+#    #+#             */
/*   Updated: 2024/11/16 15:17:04 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_atoi(char **str, bool *a)
{
	int		sign;
	int		num;
	bool	b;

	num = 0;
	sign = 1;
	b = false;
	skip_spaces_ptr(&(*str));
	check_sign(&(*str), &sign);
	while (**str == '0')
		(*str)++;
	while (**str >= 48 && **str <= 57)
	{
		b = true;
		num = (num * 10) + (**str - 48);
		if (num > 255)
			return (*a = true, 0);
		(*str)++;
	}
	if ((num == 0 && b == false) || sign < 0)
		return (*a = true, 0);
	return (num * sign);
}
void	skip_spaces_ptr(char **line)
{
	while ((**line >= 9 && **line <= 13) || **line == 32 || **line == ',')
		(*line)++;
}

void	check_sign(char **str, int *sign)
{
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		str++;
	}
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

int	table_size(char ** map)
{
	int		i;
	
	i = 0;
	if (!map || !map[0])
		return (0);
	while (map[i])
		i++;
	return (i);
}
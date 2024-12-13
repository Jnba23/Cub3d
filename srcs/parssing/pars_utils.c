/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:18:27 by asayad            #+#    #+#             */
/*   Updated: 2024/11/12 13:31:11 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

char	*ft_strdup_c(char *s, char c)
{
	char	*r;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != c)
		i++;
	j = 0;
	r = malloc(i + 1);
	if (!r)
		return (NULL);
	while (j < i)
	{
		r[j] = s[j];
		j++;
	}
	r[j] = '\0';
	return (r);
}

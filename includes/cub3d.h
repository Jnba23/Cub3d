/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:41 by asayad            #+#    #+#             */
/*   Updated: 2024/11/09 16:33:06 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <MLX42.h>
# include <get_next_line.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_map
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				ceiling;
	int				floor;
	long long		red_c;
	long long		green_c;
	long long		blue_c;
	long long		red_f;
	long long		green_f;
	long long		blue_f;
	bool			map_in;
	int				prev_line_l;
	int				wall_begin_indx;
	bool			player_in;
	int				p_pos_x;
	int				p_pos_j;
	t_list			**map;
	char			**map_2d;
	int				map_size;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	
}	t_map;

void		initialize_map(t_map *map_inf);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
t_list		*check_infile(char *in, t_map *map_inf);
int			check_if_valid_data(t_list **in_list, t_map *map_inf);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
char		*rm_spaces(char *s);
int			analyze_line(t_list *file_nd, t_map *map_inf);
int			colors_nd_texture(char *l, t_map *map_inf);
int			open_textures(char *l, t_map *direction, char *dir);
int			textures(char *l, mlx_texture_t *direction);
int			map_in(t_list *file_nd, t_map *map_inf);
int			check_rest_of_line(char *l);
int			check_fst_line(char *l);
const char	*find_path(char *l);
int			map_analysis(t_map *map_inf);
int			check_empty_lines(t_map *map_inf);
int			map_char(char *s);
void		ft_putendl_fd(char *s, int fd);
int			map_elements(t_map *map_inf);
int			check_color(char *l, t_map *map_inf, char c);
char		*ft_strdup_c(char *s, char c);
int			rgb(char *red, char *green, char *blue);
int			cub_floor(t_map *map_inf, char *red, char *green, char *blue);
int			ceiling(t_map *map_inf, char *red, char *green, char *blue);
long		ft_atoi(char *str);
int			ft_isdigit(int c);
int			is_empty(char *l);
int			cnvrt_lst_2_map(t_map *map_inf);
int			check_rest_of_map(t_list **map);
void		free_table(char **map, int j);
int			check_nd_fill_map(t_map *map_inf);
void		ft_strcpy(char *src, char *dst);
int			check_next_line(int pre_l, char **map_line, int idx);
#endif
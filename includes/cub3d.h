/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:41 by asayad            #+#    #+#             */
/*   Updated: 2025/01/23 20:38:07 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

			// relink in this file

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <MLX42.h>
# include <get_next_line.h>
# include <errno.h>
# include <strings.h>
# include <string.h>
# include <math.h>

typedef unsigned int	color;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 1200
# define TILE_SIZE	64
# define MINI_MAP_RADIUS ((float)(SCREEN_WIDTH * 0.08))  
# define MMAP_DIAMETER MINI_MAP_RADIUS * 2
# define SCALE (float)(MMAP_DIAMETER / (8 * TILE_SIZE))
# define RADIUS_SQUARE (float)(MINI_MAP_RADIUS * MINI_MAP_RADIUS)
# define STRIP_RADIUS_SQUARE (float)((MINI_MAP_RADIUS - 10.0) * (MINI_MAP_RADIUS - 10.0))
# define FOV 60	
# define RAY_ANG (float)((float)FOV / (float)SCREEN_WIDTH)
# define PLYR_SPEED 10
# define REV_TILE (float)(1.0 / (float)TILE_SIZE)
# define PI 3.14
# define DISTANCE_P (float)(SCREEN_WIDTH / (2 * tan(FOV/2)))
# define EPSILON 0.00001496

typedef struct s_map
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				ceiling;
	int				floor;
	color			red_c;
	color			green_c;
	color			blue_c;
	color			red_f;
	color			green_f;
	color			blue_f;
	bool			map_in;
	int				prev_line_l;
	int				wall_begin_indx;
	bool			player_in;
	char			pl_dir;
	int				p_pos_x;
	int				p_pos_y;
	t_list			**map;
	char			**map_2d;
	int				map_size;
	int				map_height;
	int				map_width;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	
}	t_map;

typedef struct	s_texture
{
	mlx_image_t	*img_north; // to convert the texture into an image
	mlx_image_t	*img_south; // to convert the texture into an image
	mlx_image_t	*img_east; // to convert the texture into an image
	mlx_image_t	*img_west; // to convert the texture into an image
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		pos;
	uint8_t		*pixel;
} 	t_texture;

typedef	struct s_player
{
	int			pl_x;
	int			pl_y;
	int			walk_dir;
	int			turn_dir;
	char		pl_dir;
	float		rot_angle;
	float		rot_speed;
}	t_player;


typedef struct s_ray
{
	float	x;
	float	y;
	float	ray_lenght;
	bool	horiz;
	bool	hit_door;
	bool	up;
	bool	right;
	float	d;
	double	wall_h;
	int		bott_pix;
	int		top_pix;
} t_ray;

typedef struct s_inter
{
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	alpha;
}	t_inter;

typedef struct s_coor
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		dec_param;
}	t_coor;

typedef struct s_mmap
{
	float		img_x;
	float		img_y;
	float		gm_x0;
	float		gm_y0;
	float		gm_x;
	float		gm_y;
	int			map_x;
	int			map_y;
	float		diameter;
	float		scale;
	mlx_image_t	*n;
}	t_mmap;

typedef	struct s_game
{
	mlx_t		*game;
	mlx_image_t	*game_img;
	mlx_image_t	*mmap_image; // to draw the minimap
	t_player	*pl_inf;
	t_map		*map_inf;
	t_ray		*rays;
	t_inter		*inter;
	int			map_pix_h;
	int			map_pix_w;
	char		**map;
	float		pl_x_pix;
	float		pl_y_pix;
	bool		render;
	int			wall_h;
	float		ray_ang;
	t_texture	*text;
}	t_game;

/*			Parssing			*/
void		initialize_map(t_map *map_inf);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			check_infile(char *in, t_map *map_inf);
int			check_if_valid_data(t_list **in_list, t_map **map_inf);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
char		*rm_spaces(char *s);
int			analyze_line(t_list **file_nd, t_map **map_inf);
int			colors_nd_texture(char *l, t_map **map_inf);
int			open_textures(char *l, t_map **map_inf, char *dir);
int			textures(char *l, mlx_texture_t **direction);
int			map_in(t_list **file_nd, t_map **map_inf);
int			check_rest_of_line(char *c, t_list *l);
int			check_fst_line(t_list *l);
const char	*find_path(char *l);
int			map_analysis(t_map **map_inf);
int			check_empty_lines(t_map **map_inf);
int			map_char(char *s);
void		ft_putendl_fd(char *s, int fd);
int			map_elements(t_map **map_inf);
int			check_color(char *l, t_map **map_inf, char c);
char		*ft_strdup_c(char *s, char c);
color		colors(char *rgb_s, int i);
int			ft_atoi(char **str, bool *a);
int			ft_isdigit(int c);
int			is_empty(char *l);
int			cnvrt_lst_2_map(t_map **map_inf);
int			check_rest_of_map(t_list **map);
void		free_table(t_map **map_inf, int j);
int			check_nd_fill_map(t_map **map_inf);
void		ft_strcpy(char *src, char *dst);
int			check_pre_line(int pre_l, char **map_line, int idx);
int			table_size(char **map);
int			is_map_element(t_map *map_inf, int x, int y);
int			check_player(char **map, int i, int j);
void		skip_spaces(char *line, int *i);
void		skip_spaces_ptr(char **line);
int			check_line(t_map **map_inf, int idx);
int			check_diff_dirs(char **map, int line, int c);
void		check_sign(char **str, int *sign);
void		add_map_inf(t_map **map_inf);
void		window_init(t_game *game, t_map *map_inf);

/*			Game			*/
int			start_game(t_map *map_inf);
// void		reset_mvs_indic(t_game *game);

/*			utils		*/
float		deg2rad(float angle_deg);
float		square(float i);
void		cube3d(void *game);
void		update_map_u_d(t_game *game);
void		update_map_l_r(t_game *game);
void		render_va(t_game *game, char dir);
float		rad2deg(float angle_rad);
bool		valid_ray_intersection(t_game *game, float hx, float hy);

/*			initializing	*/
void		game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf);

/*			intersections	*/
int			va_y_up(float va);
int			va_x_right(float va);
void		inter_horizontal(t_game *game, int ray);
void		inter_vertical(t_game *game, int ray);
bool		valid_ray_intersection(t_game *game, float hx, float hy);

/*			movements		*/
int			can_move(float x, float y, t_game *game);
void		update_map_l_r(t_game *game);
void		render_move(t_game *game, char dir);
void		render_va(t_game *game, char dir);

/*			rendering		*/
void		render_2D_map(t_game *game);
void		cast_rays(t_game *game);
void		render_ray(t_game *game, t_coor *coo);
void		shortest_distance(t_game *game, int ray);
void		normalize_ang(float *alpha);
void		render_3D_game(t_game *game);
void		draw_wall(int i, t_game *game, int bott_pix, int top_pix);
void		draw_ceiling_floor(int i, t_game *game, int bott_pix, int top_pix);

/*			Mini map		*/

bool		inside_mmap(float x_pix, float y_pix);
bool		inside_strip(float x_pix, float y_pix);
void		mmap_2D(t_game *game, t_mmap *m_map);
void		mmap_cnst(t_game *game, t_mmap *m_map);
void		draw_player(t_game *game);
void	    draw_ray(t_game *game, t_coor *coo);

/*			textures		*/

int			init_textures(t_game *game);
int			assign_texture(t_game *game, int i, mlx_image_t **texture);
void		calculate_tex_x(t_game *game, mlx_image_t *texture, int i);
double		calculate_wallx(t_game *game, int i);
int			draw_textured_wall(t_game *game, int i);

#endif

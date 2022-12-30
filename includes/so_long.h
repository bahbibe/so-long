/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:46:06 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/31 00:15:03 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <mlx.h>

# define K_A 0
# define A_A 123
# define K_D 2
# define A_D 124
# define K_S 1
# define A_S 125
# define K_W 13
# define A_W 126
# define K_ESC 53
# define K_Q 12
# define SCALE 115

typedef struct s_game
{
	int		frame;
	int		moves ;
	int		len;
	int		lines;
	int		pos;
	int		colct;
	int		exit;
	int		pos_x;
	int		pos_y;
	int		end;
	char	**map;
	char	**map2;
	char	*error;
	char	*score;
	char	*score_i;
	char	*msg;
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;
}	t_game;

typedef struct s_image
{
	t_game	*game;
	void	*wall;
	void	*coll;
	void	*floor;
	void	*play;
	void	*play_r;
	void	*play_l;
	void	*play_u;
	void	*play_d;
	void	*door_o;
	void	*door_c;
	void	*ghost;
	void	*ghost1;
	void	*ghost2;
	void	*ghost3;
	void	*stair;
	void	*ok;
	void	*ko;
	int		img_width;
	int		img_height;
}	t_image;

int		move_keys(int key, t_image *img);
int		put_banner(t_game *game, char *msg);
void	put_img(t_game *game, void *img, int i, int j);
void	init_img(t_game *game, t_image *img);
void	init_player_img(t_game *game, t_image *img);
void	render_assets(t_image *img);
void	render_floor(t_game *game, t_image *img);
void	render_map(t_game *game, t_image *img);
void	to_free(char **map);
void	init_game(t_game *game, t_image *img);
char	**dup_map(t_game *game);
int		ft_line_len(char *line);
int		check_extention(char *str);
int		is_rect(t_game *game);
int		check_token_type( t_game *game);
int		check_token_count(t_game *game);
int		is_closed(t_game *game);
void	flood_fill_one(int pos_x, int pos_y, char **map);
void	flood_fill_two(int pos_x, int pos_y, char **map);
int		check_collect(t_game *game, char c);
int		check(t_game *game, char *filename);
int		read_map(t_game *game, char *filename);
void	exit_error(t_game *game);
int		set_error(t_game *game, char *msg);
void	move(t_game *game, char next, int x, int y);
void	move_player(t_game *game, t_image *img, int x, int y);
int		quit(t_game *game);
int		animate( t_image *img);

#endif
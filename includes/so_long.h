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
# include <sys/time.h>
# include <unistd.h>

# ifdef __linux__
#  define K_A 97
#  define A_A 65361
#  define K_D 100
#  define A_D 65363
#  define K_S 115
#  define A_S 65364
#  define K_W 119
#  define A_W 65362
#  define K_ESC 65307
#  define K_Q 113
# else
#  define K_A 0
#  define A_A 123
#  define K_D 2
#  define A_D 124
#  define K_S 1
#  define A_S 125
#  define K_W 13
#  define A_W 126
#  define K_ESC 53
#  define K_Q 12
# endif

# define TILE 48
# define HUD_H 32
# define FRAME_MS 16
# define MOVE_MS 110
# ifndef GHOST_DELAY
#  define GHOST_DELAY 450
# endif
# define GHOST_GLIDE 180

# define C_FLOOR 0x1B1E2B
# define C_MORTAR 0x0E0F16
# define C_BRICK 0x4A5170
# define C_COIN 0xFFC83D
# define C_PLAYER 0x4DB8FF
# define C_GHOST 0xFF5C6C
# define C_WHITE 0xF2F2F2
# define C_PUPIL 0x1A1A2E
# define C_HUD 0x0B0C12
# define C_WIN 0x3DDC84
# define C_LOSE 0xFF4D4D

typedef struct s_pt
{
	int	x;
	int	y;
}	t_pt;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		line;
	int		bpp;
	int		endian;
}	t_frame;

typedef struct s_ghost
{
	int	x;
	int	y;
	int	fx;
	int	fy;
}	t_ghost;

typedef struct s_game
{
	int		moves;
	int		len;
	int		lines;
	int		colct;
	int		pos_x;
	int		pos_y;
	int		dist_x;
	int		dist_y;
	int		end;
	int		dir;
	int		dirty;
	int		ghost_count;
	long	last_frame;
	long	move_t0;
	long	ghost_t0;
	t_pt	from;
	t_ghost	*ghosts;
	int		*dist;
	int		*queue;
	char	**map;
	char	*error;
	void	*mlx;
	void	*mlx_win;
	t_frame	fb;
	t_frame	bg;
}	t_game;

void	put_px(t_frame *f, int x, int y, int color);
void	fill_rect(t_frame *f, t_rect r, int color);
void	fill_circle(t_frame *f, t_pt c, int r, int color);
void	fill_skirt(t_frame *f, t_rect r, int phase, int color);
int		shade(int color, int delta);
void	dim_rect(t_frame *f, t_rect r, int shift);
void	draw_floor(t_frame *f, t_pt o, int seed);
void	draw_wall(t_frame *f, t_pt o, int seed);
void	draw_coin(t_frame *f, t_pt o, int phase);
void	draw_door(t_frame *f, t_pt o, int open);
void	draw_player(t_frame *f, t_pt o, int dir, int bob);
void	draw_ghost(t_frame *f, t_pt o, t_pt look, int phase);
void	draw_number(t_frame *f, t_pt p, int n, int color);
void	draw_hud(t_game *game);
int		init_frame(t_game *game, t_frame *f, int w, int h);
void	free_frame(t_game *game, t_frame *f);
void	destroy_gfx(t_game *game);
t_pt	tile_origin(int i, int j);
t_pt	player_px(t_game *game, long now);
void	build_bg(t_game *game);
void	render(t_game *game);
void	draw_items(t_game *game, long now);
void	draw_ghosts(t_game *game, long now);
void	draw_end(t_game *game);
void	put_end_text(t_game *game);
long	now_ms(void);
int		lerp(int a, int b, long t, long dur);
int		key_press(int key, t_game *game);
int		expose(t_game *game);
int		tick(t_game *game);
void	init_game(t_game *game);
int		init_window(t_game *game);
char	**dup_map(t_game *game);
void	to_free(char **map);
int		ft_line_len(char *line);
int		check_extention(char *str);
int		is_rect(t_game *game);
int		check_token_type( t_game *game);
int		check_token_count(t_game *game);
int		is_closed(t_game *game);
int		flood_fill(t_game *game, char **map);
int		check_collect(char **map, char c);
int		check(t_game *game, char *filename);
int		check_path(t_game *game);
int		read_map(t_game *game, char *filename);
void	exit_error(t_game *game);
int		set_error(t_game *game, char *msg);
void	move(t_game *game, char next, int x, int y);
void	move_player(t_game *game, int x, int y);
int		quit(t_game *game);
int		init_ghosts(t_game *game);
void	free_ghosts(t_game *game);
int		ghost_at(t_game *game, int x, int y);
int		move_ghosts(t_game *game);

#endif

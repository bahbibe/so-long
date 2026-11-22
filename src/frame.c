/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:00:00 by bahbibe           #+#    #+#             */
/*   Updated: 2026/11/22 20:00:00 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_frame(t_game *game, t_frame *f, int w, int h)
{
	if (!game || !f || !game->mlx || w <= 0 || h <= 0)
		return (1);
	f->img = mlx_new_image(game->mlx, w, h);
	if (!f->img)
		return (1);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line, &f->endian);
	f->w = w;
	f->h = h;
	if (!f->addr || f->bpp != 32)
	{
		free_frame(game, f);
		return (1);
	}
	ft_bzero(f->addr, f->line * h);
	return (0);
}

void	free_frame(t_game *game, t_frame *f)
{
	if (f && f->img && game && game->mlx)
		mlx_destroy_image(game->mlx, f->img);
	if (f)
		ft_bzero(f, sizeof(*f));
}

void	destroy_gfx(t_game *game)
{
	free_frame(game, &game->fb);
	free_frame(game, &game->bg);
	if (game->mlx && game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	game->mlx_win = NULL;
	if (game->mlx)
	{
# ifdef __linux__
		mlx_destroy_display(game->mlx);
# endif
		free(game->mlx);
	}
	game->mlx = NULL;
}

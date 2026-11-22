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

void	put_px(t_frame *f, int x, int y, int color)
{
	unsigned int	*dst;

	if (!f || !f->addr || f->bpp != 32 || x < 0 || y < 0
		|| x >= f->w || y >= f->h)
		return ;
	dst = (unsigned int *)(f->addr + y * f->line + x * 4);
	*dst = color;
}

void	fill_rect(t_frame *f, t_rect r, int color)
{
	int	x;
	int	y;

	y = r.y - 1;
	while (++y < r.y + r.h)
	{
		x = r.x - 1;
		while (++x < r.x + r.w)
			put_px(f, x, y, color);
	}
}

void	fill_circle(t_frame *f, t_pt c, int r, int color)
{
	int	dx;
	int	dy;

	dy = -r - 1;
	while (++dy <= r)
	{
		dx = -r - 1;
		while (++dx <= r)
			if (dx * dx + dy * dy <= r * r)
				put_px(f, c.x + dx, c.y + dy, color);
	}
}

void	fill_skirt(t_frame *f, t_rect r, int phase, int color)
{
	int	x;
	int	y;
	int	wave;

	x = -1;
	while (++x < r.w)
	{
		wave = (x + phase) % 12;
		if (wave > 6)
			wave = 12 - wave;
		y = r.y - 1;
		while (++y < r.y + r.h - wave)
			put_px(f, r.x + x, y, color);
	}
}

int	shade(int color, int delta)
{
	int	rgb[3];
	int	i;

	i = -1;
	while (++i < 3)
	{
		rgb[i] = ((color >> (16 - 8 * i)) & 0xFF) + delta;
		if (rgb[i] < 0)
			rgb[i] = 0;
		if (rgb[i] > 255)
			rgb[i] = 255;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/* darken a region: every channel is shifted right by `shift` bits */
void	dim_rect(t_frame *f, t_rect r, int shift)
{
	unsigned int	*px;
	int				x;
	int				y;

	if (!f || !f->addr || f->bpp != 32)
		return ;
	y = r.y - 1;
	while (++y < r.y + r.h)
	{
		x = r.x - 1;
		while (++x < r.x + r.w)
		{
			if (x < 0 || y < 0 || x >= f->w || y >= f->h)
				continue ;
			px = (unsigned int *)(f->addr + y * f->line + x * 4);
			*px = (*px >> shift) & ((0xFF >> shift) * 0x010101);
		}
	}
}

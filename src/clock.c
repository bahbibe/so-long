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

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* a + (b - a) * t / dur, with t clamped to [0, dur] */
int	lerp(int a, int b, long t, long dur)
{
	if (t < 0)
		t = 0;
	if (t > dur)
		t = dur;
	return (a + (int)((b - a) * t / dur));
}

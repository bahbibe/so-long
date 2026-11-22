/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:17:06 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/31 00:27:27 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_image	img;

	if (ac != 2)
	{
		ft_putstr_fd("Error:\nUsage: ./so_long <map_file.ber>\n", 2);
		exit(1);
	}
	init_game(&game);
	if (check(&game, av[1]) || init_ghosts(&game)
		|| init_window(&game, &img))
		exit_error(&game);
	render_assets(&img);
	mlx_key_hook(game.mlx_win, move_keys, &img);
	mlx_loop_hook(game.mlx, animate, &img);
	mlx_hook(game.mlx_win, 17, 0, quit, &game);
	mlx_loop(game.mlx);
	return (0);
}

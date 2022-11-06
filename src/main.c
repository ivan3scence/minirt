/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// KEYCODES
// LINUX
#ifdef LINUX
# define ESC 65307

#endif

// MACOS

#ifdef MACOS

# define ESC 53

#endif

static int	close_win(void *inf)
{
	ft_putstr_fd(BYE, 1);
	exit(0);
	(void)inf;
	return (0);
}

int	key(int keycode, t_inf *inf)
{
	if (keycode == ESC)
		close_win(inf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_inf	*inf;

	if (argc < 2)
	{
		ft_putstr_fd("o_O?\twhere is the map?\n", 2);
		exit(GAY);
	}
	inf = parse(argv[1]);
	inf->mlx = mlx_init();
	inf->win = mlx_new_window(inf->mlx, WIDTH, HEIGHT, "miniRT");
	inf->img = mlx_new_image(inf->mlx, WIDTH, HEIGHT);
	inf->addr = mlx_get_data_addr(inf->img, &inf->bpp, &inf->line_length,
			&inf->endian);
	ray_tracing(inf, 0, 0, (double)HEIGHT / 2);
	mlx_key_hook(inf->win, key, &inf);
	mlx_hook(inf->win, 17, 0, close_win, &inf);
	mlx_loop(inf->mlx);
}

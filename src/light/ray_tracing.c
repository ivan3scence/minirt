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

t_vplane	get_view_plane(double width, double height, unsigned char fov)
{
	t_vplane	vplane;

	vplane.width = 2 * tan(fov / 2 * M_PI / 180);
	vplane.fov = fov;
	vplane.ratio = width / height;
	vplane.height = vplane.width / vplane.ratio;
	vplane.x_pixel = vplane.width / width;
	vplane.y_pixel = vplane.height / height;
	return (vplane);
}

void	ray_tracing(t_inf *inf, int mlx_y, int mlx_x, double y)
{
	t_rt	rt;

	rt.vplane = get_view_plane(WIDTH, HEIGHT, inf->cam.fov);
	while (y > -HEIGHT / 2)
	{
		rt.ray_coord[1] = y * rt.vplane.y_pixel;
		rt.x = -WIDTH / 2;
		mlx_x = -1;
		while (rt.x < WIDTH / 2)
		{
			rt.ray_coord[0] = rt.x * rt.vplane.x_pixel;
			rt.ray = new_dot(rt.ray_coord[0], rt.ray_coord[1], -1);
			normalize_vector(&rt.ray);
			inf->ray = &rt.ray;
			get_color(&inf->cam.view_point, &rt.color,
				START_RECURSION, inf);
			my_mlx_pixel_put(inf, ++mlx_x, mlx_y,
				create_trgb(0, rt.color.r, rt.color.g, rt.color.b));
			++rt.x;
		}
		++mlx_y;
		--y;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}

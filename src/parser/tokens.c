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

char	set_ambient(t_inf *inf, char **split)
{
	if (ft_arrlen(split) != 3)
		return (0);
	inf->amb.ratio = ft_dbatoi(split[1], inf);
	if (inf->amb.ratio < -1 || inf->amb.ratio > 1)
		free_exit(AMB_RANGE, inf, SYNTAX_ERROR);
	inf->amb.rgb = set_rgb(inf, split[2]);
	++inf->amb.quantity;
	return (1);
}

char	set_light(t_inf *inf, char **split)
{
	if (ft_arrlen(split) != 4)
		return (0);
	inf->light.l_point = set_coordinates(inf, split[1], NOT_NORMAL);
	inf->light.brightness = ft_dbatoi(split[2], inf);
	inf->light.rgb = set_rgb(inf, split[3]);
	return (1);
}

char	set_sphere(t_inf *inf, char **split)
{
	t_figure	*sphere;
	t_figure	*last;

	if (!(ft_arrlen(split) == 5 || ft_arrlen(split) == 4))
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	sphere = (t_figure *)malloc(sizeof(t_figure));
	if (!sphere)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	sphere->type = SPHERE_TYPE;
	sphere->coordinates = set_coordinates(inf, split[1], NOT_NORMAL);
	sphere->rgb = set_rgb(inf, split[3]);
	sphere->radius = set_radius(ft_dbatoi(split[2], inf), inf);
	if (ft_arrlen(split) == 5)
		sphere->refl = ft_atoi(split[4]);
	sphere->next = NULL;
	if (!inf->figures)
		inf->figures = sphere;
	else
	{
		last = ft_last_figure(inf->figures);
		last->next = sphere;
	}
	return (1);
}

char	set_plane(t_inf *inf, char **split)
{
	t_figure	*plane;
	t_figure	*last;

	if (ft_arrlen(split) != 4 && ft_arrlen(split) != 5)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	plane = (t_figure *)malloc(sizeof(t_figure));
	if (!plane)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	plane->type = PLANE_TYPE;
	plane->coordinates = set_coordinates(inf, split[1], NOT_NORMAL);
	plane->rgb = set_rgb(inf, split[3]);
	plane->orientation_vec = set_coordinates(inf, split[2], NORMAL);
	if (ft_arrlen(split) == 5)
		plane->refl = ft_atoi(split[4]);
	plane->next = NULL;
	if (!inf->figures)
		inf->figures = plane;
	else
	{
		last = ft_last_figure(inf->figures);
		last->next = plane;
	}
	return (1);
}

char	set_cylinder(t_inf *inf, char **split, char type)
{
	t_figure	*cylinder;
	t_figure	*last;

	if (ft_arrlen(split) != 6)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	cylinder = (t_figure *)malloc(sizeof(t_figure));
	if (!cylinder)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	cylinder->type = type;
	cylinder->coordinates = set_coordinates(inf, split[1], NOT_NORMAL);
	cylinder->orientation_vec = set_coordinates(inf, split[2], NORMAL);
	cylinder->radius = set_radius(ft_dbatoi(split[3], inf), inf);
	cylinder->height = (double)ft_dbatoi(split[4], inf);
	cylinder->rgb = set_rgb(inf, split[5]);
	cylinder->next = NULL;
	if (!inf->figures)
		inf->figures = cylinder;
	else
	{
		last = ft_last_figure(inf->figures);
		last->next = cylinder;
	}
	return (1);
}

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

double	set_radius(double diametr, t_inf *inf)
{
	if (diametr > 90000 || diametr <= 0)
		free_exit(BAD_RADIUS, inf, SYNTAX_ERROR);
	return (diametr / 2.0);
}

t_rgb	set_rgb(t_inf *inf, char *str)
{
	char	**split;
	t_rgb	rgb;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	rgb = new_rgb(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), inf);
	ft_clean_split(split);
	return (rgb);
}

t_dot	set_coordinates(t_inf *inf, char *str, char flag)
{
	char	**split;
	double	atois[3];
	t_dot	dot;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
		free_exit(NUM_COORDS, inf, SYNTAX_ERROR);
	atois[0] = ft_dbatoi(split[0], inf);
	atois[1] = ft_dbatoi(split[1], inf);
	atois[2] = ft_dbatoi(split[2], inf);
	if (flag && (atois[0] > 1.0 || atois[1] > 1.0
			|| atois[2] > 1.0 || atois[0] < -1.0 || atois[1] < -1.0
			|| atois[2] < -1.0))
		free_exit(NORMAL_RANGE, inf, SYNTAX_ERROR);
	if (flag && !atois[0] && !atois[1] && !atois[2])
		free_exit(ZERO_NORM, inf, SYNTAX_ERROR);
	if (fabs(atois[0]) > 100000 || fabs(atois[1]) > 100000
		|| fabs(atois[2]) > 100000)
		free_exit(COORD_RANGE, inf, SYNTAX_ERROR);
	dot = new_dot(atois[0], atois[1], atois[2]);
	ft_clean_split(split);
	return (dot);
}

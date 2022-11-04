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

static int	ends_with(char *str, char *end)
{
	char	*find;
	int		fd;

	find = str + ft_strlen(str) - ft_strlen(end);
	if (!ft_strnstr(find, end, ft_strlen(end)))
		free_exit(RT, NULL, CUM);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		free_exit(FILE_ERR, NULL, SEX);
	return (fd);
}

static char	set_camera(t_inf *inf, char **split)
{
	double	tmp_fov;

	if (ft_arrlen(split) != 4)
		return (0);
	inf->cam.view_point = set_coordinates(inf, split[1], NOT_NORMAL);
	inf->cam.n_vector = set_coordinates(inf, split[2], NORMAL);
	tmp_fov = ft_atoi(split[3]);
	if (tmp_fov <= 0 || tmp_fov >= 180)
		free_exit(FOV_GOVNO, inf, SYNTAX_ERROR);
	inf->cam.fov = tmp_fov;
	++inf->cam.quantity;
	return (1);
}

static char	analize(t_inf *inf, char *line)
{
	char	**split;
	char	errors;

	errors = 0;
	split = ft_split(line, ' ');
	if (ft_strncmp(split[0], "A", 2) == 0 && !inf->amb.quantity)
		errors += set_ambient(inf, split);
	else if (ft_strncmp(split[0], "C", 2) == 0 && !inf->cam.quantity)
		errors += set_camera(inf, split);
	else if (ft_strncmp(split[0], "L", 2) == 0)
		errors += set_light(inf, split);
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		errors += set_sphere(inf, split);
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		errors += set_plane(inf, split);
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		errors += set_cylinder(inf, split, CYLINDER_TYPE);
	else if (ft_strncmp(split[0], "cn", 3) == 0)
		errors += set_cylinder(inf, split, CONE_TYPE);
	else
		free_exit(NO_TOKEN, inf, SYNTAX_ERROR);
	if (!errors)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	split = free_split(split);
	return (1);
}

void	check_undef(t_inf *inf)
{
	if (inf->cam.quantity == 0)
		free_exit(NO_CUUM, inf, SYNTAX_ERROR);
	if (inf->amb.quantity == 0)
		free_exit(NO_AMB, inf, SYNTAX_ERROR);
}

t_inf	*parse(char *filename)
{
	char	*line;
	t_inf	*inf;
	int		fd;

	fd = ends_with(filename, ".rt");
	inf = (t_inf *)malloc(sizeof(t_inf));
	if (!inf)
		exit(1);
	ft_memset(inf, 0, sizeof(t_inf));
	line = get_next_line(fd);
	while (line)
	{
		if (!analize(inf, line))
		{
			free(inf);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_undef(inf);
	return (inf);
}

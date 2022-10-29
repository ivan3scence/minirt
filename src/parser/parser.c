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

static char	set_ambient(t_inf *inf, char **split)
{
	if (ft_arrlen(split) != 3)
		return (0);
	inf->amb.ratio = ft_dbatoi(split[1]);
	inf->amb.rgb = set_rgb(inf, split[2]);
	return (1);
}

static char	set_camera(t_inf *inf, char **split)
{
	if (ft_arrlen(split) != 4)
		return (0);
	inf->cam.view_point = set_coordinates(inf, split[1]);
	inf->cam.n_vector = set_coordinates(inf, split[2]);
	inf->cam.fov = ft_atoi(split[3]);
	return (1);
}

static char	set_light(t_inf *inf, char **split)
{
	if (ft_arrlen(split) != 4)
		return (0);
	inf->light.l_point = set_coordinates(inf, split[1]);
	inf->light.brightness = ft_dbatoi(split[2]);
	inf->light.rgb = set_rgb(inf, split[3]);
	return (1);
}

static char	set_sphere(t_inf *inf, char **split)
{
	t_figure	*sphere;
	t_figure	*last;

	if (ft_arrlen(split) != 5)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	sphere = (t_figure *)malloc(sizeof(t_figure));
	if (!sphere)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	sphere->type = SPHERE_TYPE;
	sphere->coordinates = set_coordinates(inf, split[1]);
	sphere->rgb = set_rgb(inf, split[3]);
	sphere->radius = ft_dbatoi(split[2]) / 2.0;
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

static char	set_plane(t_inf *inf, char **split)
{
	t_figure	*plane;
	t_figure	*last;

	if (ft_arrlen(split) != 5)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	plane = (t_figure *)malloc(sizeof(t_figure));
	if (!plane)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	plane->type = PLANE_TYPE;
	plane->coordinates = set_coordinates(inf, split[1]);
	plane->rgb = set_rgb(inf, split[3]);
	plane->orientation_vec = set_coordinates(inf, split[2]);
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

static char	set_cylinder(t_inf *inf, char **split, char type)
{
	t_figure	*cylinder;
	t_figure	*last;

	if (ft_arrlen(split) != 7)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	cylinder = (t_figure *)malloc(sizeof(t_figure));
	if (!cylinder)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	cylinder->type = type;
	cylinder->coordinates = set_coordinates(inf, split[1]);
	cylinder->orientation_vec = set_coordinates(inf, split[2]);
	//normalize_vector(&cylinder->orientation_vec);
	//printf("%g:%g:%g\n", cylinder->orientation_vec.x, cylinder->orientation_vec.y, cylinder->orientation_vec.z);
	cylinder->radius = ft_dbatoi(split[3]) / 2.0;
	cylinder->height = (double)ft_dbatoi(split[4]);
	//if (type == CYLINDER_TYPE)
	//	cylinder->height /= 2.0;
	cylinder->rgb = set_rgb(inf, split[5]);
	cylinder->refl = ft_atoi(split[6]);
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

static char	analize(t_inf *inf, char *line)
{
	char	**split;
	char	errors;

	errors = 0;
	split = ft_split(line, ' ');
	if (ft_strncmp(split[0], "A", 2) == 0)
		errors += set_ambient(inf, split);
	else if (ft_strncmp(split[0], "C", 2) == 0)
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
	if (!errors)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	split = free_split(split);
	return (1);
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
	return (inf);
}

#include "minirt.h"

int	ft_arrlen(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

double	ft_dbatoi(char *str)
{
	char	*frac;
	double	frac_i;
	char	minus;
	int		zel;

	minus = 0;
	if (*str == '-')
		minus = 1;
	frac = ft_strchr(str, '.');
	frac_i = 0;
	if (frac)
		frac_i = ((double)ft_atoi(frac + 1)) / pow(10, ft_strlen(frac + 1));
	zel = ft_atoi(str);
	if (!zel && minus)
		return (-frac_i);
	return (ft_atoi(str) + frac_i);
}

void	ft_clean_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

t_rgb	set_rgb(t_inf *inf, char *str)
{
	char	**split;
	t_rgb	rgb;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	rgb = new_rgb(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	ft_clean_split(split);
	return (rgb);
}

t_dot	set_coordinates(t_inf *inf, char *str)
{
	char	**split;
	t_dot	dot;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
		free_exit(SYNTAX, inf, SYNTAX_ERROR);
	dot = new_dot(ft_dbatoi(split[0]),
			ft_dbatoi(split[1]), ft_dbatoi(split[2]));
	ft_clean_split(split);
	return (dot);
}

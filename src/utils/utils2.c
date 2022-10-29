#include "minirt.h"

t_figure	*ft_last_figure(t_figure *fig)
{
	while (fig->next)
		fig = fig->next;
	return (fig);
}

void	free_exit(char *desc, t_inf *inf, int exit_code)
{
	t_figure	*tmp;

	if (desc)
		ft_putendl_fd(desc, 2);
	if (inf && inf->mlx && inf->win)
		mlx_destroy_window(inf->mlx, inf->win);
	while (inf && inf->figures)
	{
		tmp = inf->figures->next;
		free(inf->figures);
		inf->figures = tmp;
	}
	if (exit_code != ONLY_FREE)
		exit(exit_code);
}

int	create_trgb(int t, int r, int g, int b)
{
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_inf *inf, int x, int y, int color)
{
	char	*dst;

	dst = inf->addr + (y * inf->line_length + x * (inf->bpp / 8));
	*(unsigned int *)dst = color;
}

void	*free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (NULL);
}

double	min(double a, double b)
{
	if (a <= b)
		return (a);
	return (b);
}

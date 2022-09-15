#include "minirt.h"

t_figure	*ft_last_figure(t_figure *fig)
{
	while (fig->next)
		fig = fig->next;
	return (fig);
}

void 	free_exit(char *desc, t_inf *inf, int exit_code)
{
	t_figure 	*tmp;

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
//	printf("%x\n", t << 24 | r << 16 | g << 8 | b);
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_inf *inf, int x, int y, int color)
{
	char	*dst;

	dst = inf->addr + (y * inf->line_length + x * (inf->bpp / 8));
	*(unsigned int *)dst = color;
}

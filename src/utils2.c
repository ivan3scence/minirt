#include "minirt.h"

t_figure	*ft_last_figure(t_figure *fig)
{
	while (fig->next)
		fig = fig->next;
	return (fig);
}

void 	free_exit(char *desc, t_inf *inf, unsigned char exit_code)
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
	exit(exit_code);
}
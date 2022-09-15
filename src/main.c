#include "minirt.h"

int	main(int argc, char **argv)
{
	t_inf	*inf;
	//printf("%g %g %g %g %g %g\n", ft_dbatoi("0"), ft_dbatoi("0.1"), ft_dbatoi("123.321"), ft_dbatoi("00000"), ft_dbatoi("123456"), ft_dbatoi("0.000004"));
	//printf("%g\n", ft_dbatoi("123.321"));
	if (argc < 2)
	{
		ft_putstr_fd("o_O?\twhere is the map?\n", 2);
		exit(GAY);
	}
	inf = parse(argv[1]);
	printf("ratio %g  r %d g %d b %d\n", inf->amb.ratio,  inf->amb.rgb.r,  inf->amb.rgb.g, inf->amb.rgb.b);
	printf("x %g y %g z %g x %g y %g z %g fov %d\n", inf->cam.view_point.x,inf->cam.view_point.y,inf->cam.view_point.z,  inf->cam.n_vector.x,inf->cam.n_vector.y,inf->cam.n_vector.z,  inf->cam.fov);
	printf("x %g y %g z %g brightness %g r %d g %d b %d\n", inf->light.l_point.x,inf->light.l_point.y,inf->light.l_point.z, inf->light.brightness,inf->light.rgb.r, inf->light.rgb.g, inf->light.rgb.b);
	printf("x %g y %g z %g d %g r %d g %d b %d type %d\n", inf->figures->coordinates.x,inf->figures->coordinates.y,inf->figures->coordinates.z, inf->figures->sphere_diametr, inf->figures->rgb.r, inf->figures->rgb.g, inf->figures->rgb.b, inf->figures->type);
	printf("x %g y %g z %g vx %g vy %g vz %g r %d g %d b %d type %d\n", inf->figures->next->coordinates.x,inf->figures->next->coordinates.y,inf->figures->next->coordinates.z,
		   inf->figures->next->orientation_vec.x,inf->figures->next->orientation_vec.y,inf->figures->next->orientation_vec.z,
		   inf->figures->next->rgb.r, inf->figures->next->rgb.g, inf->figures->next->rgb.b, inf->figures->next->type);
	printf("x %g y %g z %g vx %g vy %g vz %g r %d g %d b %d type %d cyl_d %g cyl_h %g\n", inf->figures->next->next->coordinates.x,inf->figures->next->next->coordinates.y,inf->figures->next->next->coordinates.z,
			inf->figures->next->next->orientation_vec.x,inf->figures->next->next->orientation_vec.y,inf->figures->next->next->orientation_vec.z,
		   	inf->figures->next->next->rgb.r, inf->figures->next->next->rgb.g, inf->figures->next->next->rgb.b, inf->figures->next->next->type, inf->figures->next->next->cylinder_diametr, inf->figures->next->next->cylinder_height);
	free_exit(NULL, inf, 0);
}

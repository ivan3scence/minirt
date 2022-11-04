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

int	ft_arrlen(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

double	min(double a, double b)
{
	if (a <= b)
		return (a);
	return (b);
}

double	ft_dbatoi(char *str, t_inf *inf)
{
	char	*frac;
	double	frac_i;
	char	minus;
	int		zel;

	minus = 0;
	if (*str == '-')
		minus = 1;
	zel = minus - 1;
	while (str[++zel] && (ft_isdigit(str[zel]) || str[zel] == '.'))
		;
	if (str[zel])
		free_exit(NOT_DIGIT, inf, SYNTAX_ERROR);
	frac = ft_strchr(str, '.');
	if (frac && (*str == '.' || frac - str == minus))
		free_exit(WRONG_DOT, inf, SYNTAX_ERROR);
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

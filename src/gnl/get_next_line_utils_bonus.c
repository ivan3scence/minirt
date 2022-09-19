/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:22:14 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/18 21:22:15 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		s11;
	int		s22;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	s22 = 0;
	s11 = 0;
	while (s1[s22])
	{
		s3[s22] = s1[s22];
		s22++;
	}
	while (s2[s11])
		s3[s22++] = s2[s11++];
	s3[s22] = '\0';
	return (s3);
}

char	*ft_strdup(const char *s)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s1)
		return (0);
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *d, const char *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (ft_strlen(s));
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (ft_strlen(s));
}

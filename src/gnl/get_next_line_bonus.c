/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:21:47 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/18 21:21:49 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*last[8192];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	last[fd] = ft_read(fd, buf, last[fd]);
	free (buf);
	line = ft_before_n(last[fd]);
	last[fd] = ft_after_n(last[fd]);
	return (line);
}

char	*ft_read(int fd, char *buf, char *last)
{
	int		t;
	char	*tmp;

	t = 1;
	if (!last)
		last = ft_strdup("");
	while (t && ft_n(last))
	{
		t = read (fd, buf, BUFFER_SIZE);
		if (t < 0)
		{
			free(last);
			return (NULL);
		}
		buf[t] = '\0';
		tmp = last;
		last = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (last);
}

int	ft_n(char *last)
{
	while (*last)
	{
		if (*last == '\n')
			return (0);
		last++;
	}
	return (1);
}

char	*ft_before_n(char *last)
{
	char	*s;
	int		i;

	i = 0;
	if (!last)
		return (NULL);
	while (last[i] && (last[i] != '\n'))
		i++;
	s = (char *)malloc (sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	ft_strlcpy(s, last, i + 2);
	if (s[0] == '\0')
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*ft_after_n(char *last)
{
	int		i;
	char	*s;

	i = 0;
	if (!last)
		return (NULL);
	while (last[i] && (last[i] != '\n'))
		i++;
	if (last[i] == '\0')
	{
		free(last);
		return (NULL);
	}
	s = (char *)malloc (sizeof(char) * (ft_strlen(last) - i + 1));
	if (!s)
	{
		free(last);
		return (NULL);
	}
	ft_strlcpy(s, &last[i + 1], ft_strlen(last) - i + 1);
	free(last);
	return (s);
}

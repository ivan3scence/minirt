/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:21:57 by sdonny            #+#    #+#             */
/*   Updated: 2021/10/18 21:21:59 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 50

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int		ft_n(char *last);
char	*ft_read(int fd, char *buf, char *last);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_before_n(char *last);
size_t	ft_strlcpy(char *d, const char *s, size_t n);
char	*ft_after_n(char *last);
#endif

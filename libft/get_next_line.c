/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:29:27 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/15 19:42:44 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		read_file(int fd, char **a, char **n)
{
	int		r;
	char	*temp;
	char	*buf;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (!(*n = ft_strchr(*a, '\n')) &&
	(r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = 0;
		temp = *a;
		if (!(*a = ft_strjoin(*a, buf)))
			return (-1);
		ft_strdel(&temp);
	}
	ft_strdel(&buf);
	return (r);
}

int		get_next_line(const int fd, char **line)
{
	static char	*a[10240];
	int			r;
	char		*temp;
	char		*n;

	if (fd < 0 || fd > 10240 || !line || (!a[fd] && !(a[fd] = ft_strnew(1))))
		return (-1);
	r = read_file(fd, &a[fd], &n);
	if (r == -1 || !(temp = a[fd]))
		ft_strdel(&a[fd]);
	if (r == -1 || !*a[fd])
		return (r == -1 ? -1 : 0);
	if (n)
		*line = ft_strsub(a[fd], 0, n - a[fd]);
	else
	{
		if (!(*line = ft_strdup(a[fd])))
		{
			ft_strdel(&a[fd]);
			return (-1);
		}
	}
	a[fd] = ft_strsub(a[fd], LEN(*line) + R(n), LEN(a[fd]) - LEN(*line) - R(n));
	ft_strdel(&temp);
	return (1);
}

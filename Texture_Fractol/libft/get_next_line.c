/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:17:34 by aperesad          #+#    #+#             */
/*   Updated: 2018/01/22 15:17:37 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*saving(char *save, char *buff)
{
	size_t	a;
	size_t	b;
	char	*ptr;

	a = 0;
	b = 0;
	if (save)
		a = ft_strlen(save);
	if (buff)
		b = ft_strlen(buff);
	ptr = (char *)malloc(sizeof(*ptr) * (a + b + 1));
	ft_bzero(ptr, a + b + 1);
	ft_strncpy(ptr, save, a);
	ft_strcat(ptr, buff);
	free(buff);
	free(save);
	return (ptr);
}

int			check(char **save, char **buff, char **line)
{
	char	*tmp;
	char	*s;
	int		next;

	tmp = saving(*save, *buff);
	*save = tmp;
	s = ft_strchr(*save, '\n');
	if (s != NULL)
	{
		next = s - *save;
		ft_memset(*save + next, '\0', 1);
		*line = ft_strdup(*save);
		*save = ft_strdup(*save + next + 1);
		free(tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char *save[32000];
	char		*buff;
	int			nextline;
	int			a;

	if (!line || BUFF_SIZE < 1 || fd < 0 || !(buff = ft_strnew(BUFF_SIZE))
		|| read(fd, buff, 0) < 0)
		return (-1);
	while ((a = read(fd, buff, BUFF_SIZE)) > 0)
	{
		nextline = check(&save[fd], &buff, line);
		if (nextline == 1)
			return (1);
		buff = ft_strnew(BUFF_SIZE);
	}
	if ((nextline = check(&save[fd], &buff, line)))
		return (1);
	if (ft_strlen(save[fd]) > 0)
	{
		*line = ft_strdup(save[fd]);
		ft_strdel(&save[fd]);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:43:16 by aperesad          #+#    #+#             */
/*   Updated: 2017/12/11 10:43:28 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	ret(char *s, int b);
void	end(char *map);
void	freemap(char *map, char c);
void	pst_lft(char *s, char *map, int l, int f);
void	pst_rght(char *s, char *map, int l, int f);
void	pst(char *s, char *map, int l, int f);
int		trypst_lft(char *s, char *map, int l, int f);
int		trypst_rght(char *s, char *map, int l, int f);
int		trypst2(char *s, char *map, int l, int f);
char	*trypst(char *s, char *map, int f, int j);
char	*do_map(int h);
int		krn(int f);
int		check2(char *s, int i, int l);
int		check(char *s, int l);
int		howmf_ret(char *s, int i, int f);
int		howmf(char *s, int i, int f, int o);
char	*str(char *s, int l);

#endif

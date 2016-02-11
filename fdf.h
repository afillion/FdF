/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 20:39:57 by afillion          #+#    #+#             */
/*   Updated: 2016/02/11 23:24:53 by afillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# define SIZE 1820

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	char			*filename;
	int				**dot;
	int				nline;
	int				ncol;
	int				zoom;
	int				height;
	int				shifting;
	int				updown;
	int				color;
	int				angle;
}					t_env;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_line;

typedef struct		s_draw
{
	int				iso;
	int				i;
	int				j;
	int				x;
	int				y;
}					t_draw;

int					count_word(const char *s, char c);
void				struct_init(t_env *e);
void				parse(char *map, t_env *e);
void				ft_mlx(t_env *e);
void				color(int x, t_env *e);
void				draw(t_env e);
void				draw_x(t_env *e, t_draw *d);
void				draw_y(t_env *e, t_draw *d);
void				trace(t_pos *p1, t_pos *p2, t_env *e);
void				put_overlay(t_env *e);

#endif

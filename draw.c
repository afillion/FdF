/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:24:51 by afillion          #+#    #+#             */
/*   Updated: 2016/02/17 11:00:29 by afillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		trace(t_pos *p1, t_pos *p2, t_env *e)
{
	t_line	l;

	l.dx = ft_abs(p2->x - p1->x);
	l.sx = p1->x < p2->x ? 1 : -1;
	l.dy = ft_abs(p2->y - p1->y);
	l.sy = p1->y < p2->y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		mlx_pixel_put(e->mlx, e->win, p1->y, p1->x, e->color);
		if (p1->x == p2->x && p1->y == p2->y)
			break ;
		l.e2 = l.err;
		if (l.e2 > -l.dx)
		{
			l.err -= l.dy;
			p1->x += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.err += l.dx;
			p1->y += l.sy;
		}
	}
}

void		draw_x(t_env *e, t_draw *d)
{
	t_pos p1;
	t_pos p2;

	e->z = (e->dot[d->i][d->j] + e->dot[d->i + 1][d->j]) / 2;
	color(e);
	p1.y = (d->j * e->zoom) + ((e->nline - d->i) * e->angle) + e->shifting;
	p1.x = (d->i * e->zoom) - (e->dot[d->i][d->j] * e->height) + e->updown;
	p2.y = (d->j * e->zoom) + ((e->nline - (d->i + 1)) * e->angle) +
		e->shifting;
	p2.x = ((d->i + 1) * e->zoom) - (e->dot[d->i + 1][d->j] * e->height) +
		e->updown;
	trace(&p1, &p2, e);
}

void		draw_y(t_env *e, t_draw *d)
{
	t_pos p1;
	t_pos p2;

	e->z = (e->dot[d->i][d->j] + e->dot[d->i][d->j + 1]) / 2;
	color(e);
	p1.y = (d->j * e->zoom) + ((e->nline - d->i) * e->angle) + e->shifting;
	p1.x = (d->i * e->zoom) - (e->dot[d->i][d->j] * e->height) + e->updown;
	p2.y = ((d->j + 1) * e->zoom) + ((e->nline - d->i) * e->angle) +
		e->shifting;
	p2.x = (d->i * e->zoom) - (e->dot[d->i][d->j + 1] * e->height) + e->updown;
	trace(&p1, &p2, e);
}

void		draw(t_env e)
{
	t_draw	d;

	mlx_clear_window(e.mlx, e.win);
	put_overlay(&e);
	d.i = 0;
	while (d.i < e.nline)
	{
		d.j = 0;
		color(&e);
		while (d.j < e.ncol)
		{
			if (d.j + 1 < e.ncol)
				draw_y(&e, &d);
			if (d.i + 1 < e.nline)
				draw_x(&e, &d);
			d.j++;
		}
		d.i++;
	}
}

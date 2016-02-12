/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:20:50 by afillion          #+#    #+#             */
/*   Updated: 2016/02/12 17:55:54 by afillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color(t_env *e)
{
	if (ft_abs(e->z) == 0)
		e->color = 0x0000FF;
	if (ft_abs(e->z) == 1)
		e->color = 0x00CCFF;
	if (ft_abs(e->z) > 1)
		e->color = 0x00CC00;
	if (ft_abs(e->z) > 5)
		e->color = 0x339900;
	if (ft_abs(e->z) > 15)
		e->color = 0x996600;
	if (ft_abs(e->z) > 20)
		e->color = 0x663300;
	if (ft_abs(e->z) > 60)
		e->color = 0xFFFFFF;
}

void	put_overlay(t_env *e)
{
	mlx_string_put(e->mlx, e->win, 20, 20, 0xFF0000, "FILE : ");
	mlx_string_put(e->mlx, e->win, 90, 20, 0xFF0000, e->filename);
	mlx_string_put(e->mlx, e->win, 20, 40, 0xFF0000, "\n");
	mlx_string_put(e->mlx, e->win, 20, 60, 0xFF0000, "Commands : ");
	mlx_string_put(e->mlx, e->win, 20, 80, 0xFF0000, "W A S D = MOVE");
	mlx_string_put(e->mlx, e->win, 20, 100, 0xFF0000, "+ - (pavNUM) = ZOOM");
	mlx_string_put(e->mlx, e->win, 20, 120, 0xFF0000, "Up/Down = DEPTH");
	mlx_string_put(e->mlx, e->win, 20, 140, 0xFF0000, "Left/Right = ANGLE");
	mlx_string_put(e->mlx, e->win, 20, 160, 0xFF0000, "ESC = QUIT");
}

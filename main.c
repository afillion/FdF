/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:22:11 by afillion          #+#    #+#             */
/*   Updated: 2016/02/12 17:37:15 by afillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			expose_hook(t_env *e)
{
	draw(*e);
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == 69)
		e->zoom += 1;
	if ((keycode == 78) || (keycode == 27))
		e->zoom -= 1;
	if (keycode == 126)
		e->height += 1;
	if (keycode == 125)
		e->height -= 1;
	if (keycode == 0)
		e->shifting -= 200;
	if (keycode == 2)
		e->shifting += 200;
	if (keycode == 13)
		e->updown -= 200;
	if (keycode == 1)
		e->updown += 200;
	if (keycode == 124)
		e->angle += 2;
	if (keycode == 123)
		e->angle -= 2;
	if (keycode == 53)
		exit(0);
	draw(*e);
	return (0);
}

void		ft_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE, SIZE, "42");
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, key_hook, e);
	mlx_loop(e->mlx);
}

void		ft_open_win(t_env *e, char *map)
{
	struct_init(e);
	parse(map, e);
	ft_mlx(e);
}

int			main(int ac, char **av)
{
	t_env	e;
	int		fd;
	char	*line;
	char	*map;

	line = NULL;
	map = ft_strnew(0);
	if (ac == 2)
	{
		e.filename = av[1];
		fd = open(av[1], O_RDONLY);
		if (fd < 1)
			ft_exit("Bad file descriptor");
		while (get_next_line(fd, &line) > 0)
		{
			map = ft_strjoin(map, ft_strjoin(line, "\n"));
			free(line);
			e.nline++;
		}
		close(fd);
	}
	else
		ft_exit("Usage: ./fdf <path to map>");
	ft_open_win(&e, map);
	return (0);
}

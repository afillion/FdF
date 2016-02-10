#include "fdf.h"

void line(int x0, int y0, int x1, int y1, void *mlx, void *win, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = ft_abs(x1-x0);
	sx = x0<x1 ? 1 : -1;
	dy = abs(y1-y0);
	sy = y0<y1 ? 1 : -1;
	err = (dx>dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (x0==x1 && y0==y1)
			break;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	ft_draw(t_env e)
{
	int		i;
	int		x;
	int		j;
	int		y;
	int		iso;
	int		color;

//	x = 0;
//	y = 0;
//	while (x <= 1820)
//	{
//		while (y <= 1820)
//		{
//			mlx_pixel_put(e.mlx, e.win, y, x, 0x000000);
//			y++;
//		}
//		x++;
//		y = 0;
//	}
mlx_clear_window(e.mlx, e.win);
	i = 0;
	x = 0 + e.updown;
	iso = e.zoom * e.nline + e.shifting;
	//printf("iso = %d\n", iso);
	while (i < e.nline)
	{
		j = 0;
		y = iso;
		while (j < e.ncol)
		{
			if (ft_abs(e.dot[i][j]) > 50)
				color = 0xFFFFFF;
			else if (ft_abs(e.dot[i][j]) > 10)
				color = 0x663300;
			else if (ft_abs(e.dot[i][j]) > 3)
				color = 0x00CC00;
			if (ft_abs(e.dot[i][j]) == 0)
				color = 0x3399FF;
			//mlx_pixel_put(e.mlx, e.win, y, (x + e.dot[i][j]), 0xFF0000);
			if (y + e.zoom < e.ncol * e.zoom + iso)
				line(y, (x-e.dot[i][j] * e.height), (y+e.zoom), (x - e.dot[i][j+1] * e.height), e.mlx, e.win, color);
			if ((x + e.zoom + e.shifting < e.nline * e.zoom + iso + e.updown) && i+1<e.nline)
				line(y, (x-e.dot[i][j] * e.height), y-e.zoom, (x + e.zoom - e.dot[i+1][j] * e.height), e.mlx, e.win, color);
			//printf("j = %d\ny = %d\ndot[%d][%d] = %d\n", j, y, i, j, e.dot[i][j]);
			//printf("e.nline = %d\ne.ncol = %d\n", e.nline, e.ncol);
			j++;
			y += e.zoom;
		}
		x += e.zoom;
		iso -= e.zoom;
		i++;
	}
}

int		expose_hook(t_env *e)
{
	ft_draw(*e);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	printf("key = %d\n", keycode);
	if (keycode == 69)
	{
		e->zoom += 1;
		ft_draw(*e);
	}
	if ((keycode == 78) || (keycode == 27))
	{
		e->zoom -= 1;
		ft_draw(*e);
	}
	if (keycode == 126)
	{
		e->height += 1;
		ft_draw(*e);
	}
	if (keycode == 125)
	{
		e->height -= 1;
		ft_draw(*e);
	}
	if (keycode == 0)
	{
		e->shifting -= 90;
		ft_draw(*e);
	}
	if (keycode == 2)
	{
		e->shifting += 90;
		ft_draw(*e);
	}
	if (keycode == 13)
	{
		e->updown -= 90;
		ft_draw(*e);
	}
	if (keycode == 1)
	{
		e->updown += 90;
		ft_draw(*e);
	}
	if (keycode == 123)
	{
		e->angle += 1;
		ft_draw(*e);
	}
	if (keycode == 124)
	{
		e->angle -= 1;
		ft_draw(*e);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

//int		mouse_hook(int button, int x, int y)
//{
//	//printf("mouse button = %d(%d,%d)\n", button, x, y);
//	return (0);
//}

int		count_word(const char *s, char c)
{
	int	nb;
	int	i;
	int	check;

	i = 0;
	check = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && check)
			check = !check;
		else if (s[i] != c && !check)
		{
			nb++;
			check = !check;
		}
		i++;
	}
	return (nb);
}

int		main(int ac, char **av)
{
	t_env	e;
	int		fd;
	char	*line;
	char	*map;
	char	**split;
	int		i;
	int		j;
	char	**new;

	line = NULL;
	e.zoom = 2;
	e.shifting = 0;
	e.height = 1;
	e.updown = 0;
	e.angle = 0;
	map = ft_strnew(0);
	e.dot = NULL;
	i = 0;
	j = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			map = ft_strjoin(map, ft_strjoin(line, "\n"));
			free(line);
			e.nline++;
		}
	}
	//printf("e.nline = %d\n", e.nline);
//	ft_putstr(map);
	split = ft_strsplit(map, '\n');
	e.dot = (int**)malloc(sizeof(int*) * e.nline);
	while (split[i])
	{
		//printf("split[%d] = %s\n\n\n",i, split[i]);
		e.dot[i] = (int*)malloc(sizeof (int) * count_word(split[i], ' '));
		e.ncol = count_word(split[i], ' ');
		//printf("count_word(split[%d]) = %d\n", i, count_word(split[i], ' '));
		j = 0;
		new = ft_strsplit(split[i], ' ');
		while (new[j])
		{
			e.dot[i][j] = ft_atoi(new[j]);
			//printf("e.dot[%d][%d] = %d\n", i, j, ft_atoi(new[j]));
			j++;
		}
		i++;
	}
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1820, 1820, "42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
//	mlx_mouse_hook(e.win, mouse_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

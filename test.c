#include "fdf.h"

void line(int x0, int y0, int x1, int y1, void *mlx, void *win)
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
		mlx_pixel_put(mlx, win, x0, y0, 0xFF0000);
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

void	ft_draw(void *mlx, void *win)
{
	int		x;
	int		y;

	x = 0;
	while (x < 360)
	{
		y = 0;
		while (y < 220)
		{
			mlx_pixel_put(mlx, win, x, y, 0xFF0000);
			y += 20;
		}
		x += 20;
	}
}

int		expose_hook(t_env *e)
{
	ft_draw(e->mlx, e->win);
	return (0);
}

int		key_hook(int keycode)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	return (0);
}

int		mouse_hook(int button, int x, int y)
{
	printf("mouse button = %d(%d,%d)\n", button, x, y);
	return (0);
}

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
	int		**tab;
	int		k;
	char	**new;

	line = NULL;
	map = ft_strnew(0);
	tab = NULL;
	i = 0;
	j = 0;
	k = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			map = ft_strjoin(map, ft_strjoin(line, "\n"));
			free(line);
			k++;
		}
	}
	printf("k = %d\n", k);
	ft_putstr(map);
	split = ft_strsplit(map, '\n');
	tab = (int**)malloc(sizeof(int*) * k);
	while (split[i])
	{
		printf("split[%d] = %s\n\n\n",i, split[i]);
		tab[i] = (int*)malloc(sizeof (int) * count_word(split[i], ' '));
		printf("count_word(split[%d] = %d\n", i, count_word(split[i], ' '));
		j = 0;
		new = ft_strsplit(split[i], ' ');
		while (new[j])
		{
			tab[i][j] = ft_atoi(new[j]);
			printf("tab[%d][%d] = %d\n", i, j, ft_atoi(new[j]));
			j++;
		}
		i++;
	}
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 420, 420, "42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_mouse_hook(e.win, mouse_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

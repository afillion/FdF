#include "fdf.h"

void		line(t_pos *p1, t_pos *p2, t_env *e)
{
	t_line	l;

	l.dx = ft_abs(p2->x - p1->x);
	l.sx = p1->x < p2->x ? 1 : -1;
	l.dy = abs(p2->y - p1->y);
	l.sy = p1->y < p2->y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		mlx_pixel_put(e->mlx, e->win, p1->x, p1->y, e->color);
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

void		ft_color(int x, t_env *e)
{
	if (ft_abs(x) >= 0 && ft_abs(x) <= 1)
		e->color = 0x3399FF;
	if (ft_abs(x) > 1)
		e->color = 0x00CC00;
	if (ft_abs(x) > 20)
		e->color = 0x663300;
	if (ft_abs(x) > 60)
		e->color = 0xFFFFFF;
}

t_pos	ft_struct_pos_init(t_pos *p, t_env *e, t_draw *d)
{

}

void	ft_draw(t_env e)
{
	t_draw	d;

	mlx_clear_window(e.mlx, e.win);
	d.i = 0;
	d.x = 0 + e.updown;
	d.iso = e.zoom * e.nline + e.shifting;
	while (d.i < e.nline)
	{
		d.j = 0;
		d.y = d.iso;
		while (d.j < e.ncol)
		{
			ft_color(e.dot[d.i][d.j], &e);
			ft_struct_pos_init(&e, &d);
			if (d.y + e.zoom < e.ncol * e.zoom + d.iso)
				line(d.y, (d.x - e.dot[d.i][d.j] * e.height), (d.y + e.zoom), (d.x - e.dot[d.i][d.j + 1] * e.height), &e);
			if ((d.x + e.zoom + e.shifting < e.nline * e.zoom + d.iso + e.updown) && d.i + 1 < e.nline)
				line(d.y, (d.x - e.dot[d.i][d.j] * e.height), d.y - e.zoom, (d.x + e.zoom - e.dot[d.i + 1][d.j] * e.height), &e);
			d.j++;
			d.y += e.zoom;
		}
		d.x += e.zoom;
		d.iso -= e.zoom;
		d.i++;
	}
}

int		expose_hook(t_env *e)
{
	ft_draw(*e);
	return (0);
}

int		key_hook(int keycode, t_env *e)
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
		e->shifting -= 90;
	if (keycode == 2)
		e->shifting += 90;
	if (keycode == 13)
		e->updown -= 90;
	if (keycode == 1)
		e->updown += 90;
	if (keycode == 53)
		exit(0);
	ft_draw(*e);
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

void	ft_struct_env_init(t_env *e)
{
	e->zoom = 2;
	e->shifting = 0;
	e->height = 1;
	e->updown = 0;
	e->dot = NULL;
}

void	parse(char *map, t_env *e)
{
	int		i;
	int		j;
	char	**new;
	char	**split;

	i = 0;
	split = ft_strsplit(map, '\n');
	e->dot = (int**)malloc(sizeof(int*) * e->nline);
	while (split[i])
	{
		j = 0;
		e->dot[i] = (int*)malloc(sizeof(int) * count_word(split[i], ' '));
		e->ncol = count_word(split[i], ' ');
		new = ft_strsplit(split[i], ' ');
		while (new[j])
		{
			e->dot[i][j] = ft_atoi(new[j]);
			j++;
		}
		i++;
	}
}

void	ft_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, 1820, 1820, "42");
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, key_hook, e);
//	mlx_mouse_hook(e->win, mouse_hook, &e);
	mlx_loop(e->mlx);
}

int		main(int ac, char **av)
{
	t_env	e;
	int		fd;
	char	*line;
	char	*map;

	ft_struct_env_init(&e);
	line = NULL;
	map = ft_strnew(0);
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
	parse(map, &e);
	ft_mlx(&e);
	return (0);
}

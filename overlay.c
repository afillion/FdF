#include "fdf.h"

void	put_overlay(t_env *e)
{
	mlx_string_put(e->mlx, e->win, 20, 20, 0xFF0000, "FILE : ");
	mlx_string_put(e->mlx, e->win, 90, 20, 0xFF0000, e->filename);
	mlx_string_put(e->mlx, e->win, 20, 40, 0xFF0000, "Commands : ");
	mlx_string_put(e->mlx, e->win, 20, 60, 0xFF0000, "W, A, S, D = MOVE");
	mlx_string_put(e->mlx, e->win, 20, 80, 0xFF0000, "+, - (pavNUM) = ZOOM");
	mlx_string_put(e->mlx, e->win, 20, 100, 0xFF0000, "Up/Down arrow = DEPTH");
	mlx_string_put(e->mlx, e->win, 20, 120, 0xFF0000, "ESC = QUIT");
}

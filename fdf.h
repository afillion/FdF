#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				**dot;
	int				nline;
	int				ncol;
	int				zoom;
	int				height;
	int				shifting;
	int				updown;
	int				color;
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

void				ft_color(int x, t_env *e);
void				ft_draw(t_env e);
void				line(t_pos *p1, t_pos *p2, t_env *e);

#endif

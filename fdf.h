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
}					t_env;

int					ft_color(int x);
void				ft_draw(t_env e);
void				line(int x0, int y0, int x1, int y1, t_env *e, int color);

#endif

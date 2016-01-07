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
}					t_env;

void				ft_draw(void *mlx, void *win);

#endif

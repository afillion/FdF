#include "fdf.h"

int			count_word(const char *s, char c)
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

void		struct_init(t_env *e)
{
	e->zoom = e->ncol > e->nline ? SIZE / 2 / e->ncol : SIZE/ 2 / e->nline;
	e->shifting = (SIZE - (e->nline * e->zoom)) / 4;
	e->height = 1;
	e->updown = (SIZE - (e->ncol * e->zoom)) / 4;
	e->angle = 2;
}

void		parse(char *map, t_env *e)
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

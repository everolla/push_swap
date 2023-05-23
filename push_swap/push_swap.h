#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef	struct	s_list
{
	t_list	*preview;
    int		num; 
    int		pos;
	int 	rank;
	t_list	*next; 
}				t_list;

typedef	struct	s_sort
{
	int		hold_first;
	int		hold_second;
}				t_sort;

typedef struct s_general
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		total;
	char	**argv;
	int		argc;
	t_sort	*sort;
}				t_general;

#endif
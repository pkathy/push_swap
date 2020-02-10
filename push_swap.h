#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"
#include <stdio.h>
typedef struct	s_stack {
	int		*data;
	size_t	size;
}				t_stack;

typedef struct	s_two {
	t_stack	*a;
	t_stack	*b;
}				t_stacks;

typedef struct	s_data {
	int	next_part_a;
	int	is_a_parted;
	int	next_part_b;
	int is_b_parted;
	int b_first;
	int a_first;
	int error;
	int level;
}				t_data;


int	stack_from_source(t_stack *stack, char **source, size_t source_size);
int	stack_resize(t_stack *stack, size_t size);
int	operate(char *operation, t_stack *a, t_stack *b);
int	get_pivot(t_stacks *s, t_data *data, char stack_name);
#endif

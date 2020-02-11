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
	t_stack *a_parts;
	t_stack	*b_parts;
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

int	stack_push(t_stack *from, t_stack *to);
int	stack_from_source(t_stack *stack, char **source, size_t source_size);
int	stack_resize(t_stack *stack, size_t size);
int stack_pop(t_stack *stack);
int t_stack_push(t_stack *stack, int data);
int stack_peek(t_stack *stack);
int	operate(char *operation, t_stack *a, t_stack *b);
int	get_pivot(t_stacks *s, t_data *data, char stack_name);
int is_in_stack(t_stack *s, int k);
#endif

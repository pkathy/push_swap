#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"

typedef struct	s_stack {
	int		*data;
	size_t	size;
}				t_stack;

int	stack_from_source(t_stack *stack, char **source, size_t source_size);
int	stack_resize(t_stack *stack, size_t size);
int	operate(char *operation, t_stack *a, t_stack *b);
#endif

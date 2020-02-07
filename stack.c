#include "push_swap.h"
//temporary for atol
#include <stdlib.h>

int is_valid(char *str)
{
	int c;

	c = 0;
	while(*str)
	{
		if(!ft_isdigit(*str) || c > 10)
			return (0);
		str++;
		c++;
	}
	return (1);
}

int	is_duplicate(int *arr, int arr_size, int new)
{
	int	i;

	i = 0;
	while (i < arr_size)
		if (new == arr[i++])
			return (1);
	return (0);
}

int	handle_error(int *p)
{
	free(p);
	return (0);
}
//todo : check if there are duplicates
int	stack_from_source(t_stack *stack, char **source, size_t source_size)
{
	long	tmp;
	int		i;

	if ((i = 0) == 0 && !source)
	{
		stack->data = 0;
		stack->size = 0;
		return (1);
	}
	if (!(stack->data = ft_memalloc(source_size * sizeof(int))))
		return (0);
	stack->size = source_size;
	while (source_size-- > 0)
	{
		if(!is_valid(source[source_size]))
			return (handle_error(stack->data));
		tmp = atol(source[source_size]);
		if ((long)tmp != (int)tmp || is_duplicate(stack->data, i, tmp))
			return (handle_error(stack->data));
		stack->data[i++] = tmp;
	}
	return (1);
}

int	stack_resize(t_stack *stack, size_t size)
{
	int *tmp;

	if (size <= 0)
	{
		free(stack->data);
		stack->data = 0;
		stack->size = 0;
		return (1);
	}
	if (!(tmp = ft_memalloc(size * sizeof(int))))
		return (0);
	ft_memmove(tmp, stack->data, sizeof(int) * (stack->size > size ? size : stack->size));
	free(stack->data);
	stack->data = tmp;
	stack->size = size;
	return (1);
}
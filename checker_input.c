#include "push_swap.h"
#include <stdio.h>

static int	is_sorted(t_stack *s)
{
	size_t	i;

	i = -1;
	while (++i < s->size - 1)
		if (s->data[i] < s->data[i + 1])
			return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	char *line;

	if (argc < 2)
		return (1);
	if (!stack_from_source(&a, ++argv, argc - 1)) {
		write(2, "Error\n", 6);
		return (0);
	}
	stack_from_source(&b, 0, 0);
	while (get_next_line(0, &line))
	{
		if (!operate(line, &a, &b, 1))
			write(2, "Error\n", 6);
		free(line);
	}
	if (is_sorted(&a) && b.size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	if (a.data && a.size)
		free(a.data);
	if (b.data && a.size)
		free(b.data);
	return (0);
}
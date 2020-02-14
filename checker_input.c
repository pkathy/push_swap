#include "push_swap.h"
#include <stdio.h>

static int	is_sorted(t_stack *s)
{
	int tmp;
	int	i;

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
		printf("Error\n");
		return (0);
	}
	stack_from_source(&b, 0, 0);
	while (get_next_line(0, &line))
	{
		if (!operate(line, &a, &b, 1))
			write(2, "Error\n", 6);
		for (int i = 0; i < a.size; ++i)
			printf("%d ", a.data[i]);
		printf("      ");
		for (int i = 0; i < b.size; ++i)
			printf("%d ", b.data[i]);
		printf("\n");
		free(line);
	}
	if (is_sorted(&a) && b.size == 0)
		printf("OK\n");
	else
		printf("KO\n");
	return (0);
}
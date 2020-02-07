#include "push_swap.h"
#include <stdio.h>


int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	char *line;

	if (argc < 2)
		return (1);
	stack_from_source(&a, ++argv, argc - 1);
	stack_from_source(&b, 0, 0);
	while (get_next_line(0, &line))
	{
		if (!operate(line, &a, &b))
			write(2, "Error\n", 6);
		for (int i = 0; i < a.size; ++i)
			printf("%d ", a.data[i]);
		printf("      ");
		for (int i = 0; i < b.size; ++i)
			printf("%d ", b.data[i]);
		printf("\n");
		free(line);
	}
	return (0);
}
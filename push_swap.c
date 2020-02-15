#include "push_swap.h"

//todo : make main greate again
int	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	t_stack b_parts;
	t_stack a_parts;
	t_stacks s;

	if (argc < 2)
		return (1);
	if (!stack_from_source(&a, ++argv, argc - 1))
	{
		printf("Error\n");
		return (0);
	}
	stack_from_source(&b, 0, 0);
	stack_from_source(&b_parts, 0, 0);
	stack_from_source(&a_parts, 0, 0);

	s.b = &b;
	s.a_parts = &a_parts;
	s.b_parts = &b_parts;
	s.a = &a;
	test_sort(&s);
	operate(0, 0, 0, 3);
	free(a.data);
	free(b.data);
	free(a_parts.data);
	free(b_parts.data);
	return (0);
}


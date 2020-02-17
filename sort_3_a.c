#include "push_swap.h"

int sort_3_a2(t_stacks *s, int as, int *arr)
{
	if (arr[as - 2] < arr[as - 1] && arr[as - 1] < arr[as - 3])
	{
		operate("sa", s->a, s->b, 0);
	}
	else if (arr[as - 2] < arr[as - 3] && arr[as - 3] < arr[as - 1])
	{
		operate("sa", s->a, s->b, 0);
		operate("ra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
	}
	else if (arr[as - 1] < arr[as - 3] && arr[as - 3] < arr[as - 2])
	{
		operate("ra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
	}
	return (0);
}
int sort_3_a1(t_stacks *s, int as, int *arr)
{
	if (arr[as - 3] < arr[as - 2] && arr[as - 2] < arr[as - 1])
	{
		operate("sa", s->a, s->b, 0);
		operate("ra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
	}
	else if (arr[as - 1] < arr[as - 2] && arr[as - 2] < arr[as - 3])
	{
		return (0);
	}
	else if (arr[as - 3] < arr[as - 1] && arr[as - 1] < arr[as - 2])
	{
		operate("ra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
		operate("sa", s->a, s->b, 0);
	}
	else
		return (sort_3_a2(s, as, arr));
	return (0);
}

int sort_3_a(t_stacks *s, int part_size)
{
	if (s->a->size <= 3)
		return (sort_small(s, part_size));
	if (part_size <= 1)
		return (0);
	if (part_size == 2 && stack_peek(s->a) > s->a->data[s->a->size - 2])
		operate("sa", s->a, s->b, 0);
	if (part_size == 3)
		return (sort_3_a1(s, s->a->size, s->a->data));
	return (0);
}
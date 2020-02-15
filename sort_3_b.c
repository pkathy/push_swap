#include "push_swap.h"

int sort_3_b2(t_stacks *s, int bs, int *arr)
{
	if (arr[bs - 1] > arr[bs - 3] && arr[bs - 3] > arr[bs - 2])
	{
		operate("pa", s->a, s->b, 0);
		operate("sb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else if (arr[bs - 3] > arr[bs - 1] && arr[bs - 1] > arr[bs - 2])
	{
		operate("rb", s->a, s->b, 0);
		operate("sb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("rrb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else if (arr[bs - 2] > arr[bs - 1] && arr[bs - 1] > arr[bs - 3])
	{
		operate("sb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	return (0);
}

void sort_3_b1(t_stacks *s, int bs, int *arr)
{
	if (arr[bs - 3] > arr[bs - 2] && arr[bs - 2] > arr[bs - 1])
	{
		operate("rb", s->a, s->b, 0);
		operate("sb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("rrb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else if (arr[bs - 1] > arr[bs - 2] && arr[bs - 2] > arr[bs - 3])
	{
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else if (arr[bs - 2] > arr[bs - 3] && arr[bs - 3] > arr[bs - 1])
	{
		operate("rb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("rrb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else
		sort_3_b2(s, bs, arr);
}

int sort_3_b(t_stacks *s, int part_size)
{
	if (part_size <= 0)
		return (0);
	if (part_size == 1)
		operate("pa", s->a, s->b, 0);
	if (part_size == 2 && stack_peek(s->b) <= s->b->data[s->b->size - 2])
	{
		operate("sb", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	else if (part_size == 2 && stack_peek(s->b) > s->b->data[s->b->size - 2])
	{
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
	}
	if (part_size == 3)
		sort_3_b1(s, s->b->size, s->b->data);
	return (0);
}
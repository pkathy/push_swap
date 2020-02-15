#include "push_swap.h"

int part_size(t_stacks *s, char stack_name)
{
	int stop;
	int	i;

	if (stack_name == 'a' && !(s->a_parts->size))
		return (s->a->size);
	if (stack_name == 'b' && !(s->b_parts->size))
		return (s->b->size);
	if (stack_name == 'a')
	{
		stop = stack_peek(s->a_parts);
		i = s->a->size;
		while (--i >= 0)
			if (s->a->data[i] == stop)
				return (s->a->size - i - 1);
	}
	if (stack_name == 'b')
	{
		stop = stack_peek(s->b_parts);
		i = s->b->size;
		while (--i >= 0)
			if (s->b->data[i] == stop)
				return (s->b->size - i);
	}
	return (-1);
}

int get_pivot(t_stacks *s, char stack_name)
{
	int i;
	t_stack median;

	stack_from_source(&median, 0, 0);
	i = stack_name == 'a' ? s->a->size : s->b->size;
	if (stack_name == 'a')
		while (--i >= 0)
		{
			if (s->a_parts->size && s->a->data[i] == stack_peek(s->a_parts))
				break;
			t_stack_push(&median, s->a->data[i]);
		}
	if (stack_name == 'b')
		while (--i >= 0)
		{
			t_stack_push(&median, s->b->data[i]);
			if (s->b_parts->size && s->b->data[i] == stack_peek(s->b_parts))
				break;
		}
	return (get_median(&median, part_size(s, stack_name)));
}

int find_possible_partition(t_stacks *s, t_data *data, int pivot)
{
	int p_size;
	size_t	i;

	p_size = part_size(s, 'b');
	i = s->b->size - p_size - 1;
	while (++i < s->b->size)
	{
		if (s->b->data[i] < pivot)
		{
			data->error = 0;
			return (s->b->data[i]);
		}
	}
	data->error = 1;
	return (-1);
}

int is_there_to_push(t_stacks *s, int pivot, char stack)
{
	int		p_size;
	int		flag;
	size_t	k;

	flag = 0;
	p_size = (stack == 'b') ? part_size(s, 'b') : part_size(s, 'a');
	k = (stack == 'b') ? s->b->size - p_size - 1 : s->a->size - p_size - 1;
	if (stack == 'b')
	{
		while (++k < s->b->size)
			if (s->b->data[k] >= pivot)
				flag = 1;
	}
	else
	{
		while (++k < s->a->size)
			if (s->a->data[k] <= pivot)
				flag = 1;
	}
	return (flag);
}

#include "push_swap.h"

int b_push(t_stacks *s, t_data *data, int pivot, int *r_count)
{
	data->stop = s->a_parts->size ? stack_peek(s->a_parts) : s->a->data[0];
	while (stack_peek(s->a) != data->stop)
	{
		if (stack_peek(s->a) <= pivot) {
			if (data->b_first) {
				t_stack_push(s->b_parts, stack_peek(s->a));
				data->b_first = 0;
			}
			operate("pb", s->a, s->b, 0);
		}
		if (!is_there_to_push(s, pivot, 'a'))
			break;
		if (s->a->data[s->a->size - 1] > pivot) {
			if (stack_peek(s->a) == data->stop)
				break;
			operate("ra", s->a, s->b, 0);
			(*r_count)++;
		}
	}
	if (stack_peek(s->a) <= pivot)
		operate("pb", s->a, s->b, 0);
	return (0);
}

int push_to_b(t_stacks *s, t_data *data, int pivot)
{
	int	r_count;

	r_count = 0;
	if (!s->a->size)
		return (0);
	b_push(s, data, pivot, &r_count);
	if (s->a_parts->size != 0)
	{
		if (s->a->size - r_count < s->a->size / 2)
			while (s->a->size - r_count > 0) {
				operate("ra", s->a, s->b, 0);
				r_count++;
			}
		else
			while (r_count-- > 0)
				operate("rra", s->a, s->b, 0);
	}
	if (s->a->size > 0 && !is_in_stack(s->a, stack_peek(s->a_parts)))
		stack_pop(s->a_parts);
	return (1);
}

int a_push(t_stacks *s, t_data *data, int pivot, int *r_count)
{
	if (s->b->size && (data->bps = part_size(s, 'b')) <= 3)
	{
		sort_3_b(s, data->bps);
		stack_pop(s->b_parts);
		if (s->a->size)
			t_stack_push(s->a_parts, stack_peek(s->a));
		return (1);
	}
	if (s->a->size)
		t_stack_push(s->a_parts, stack_peek(s->a));
	data->stop = s->b_parts->size ? stack_peek(s->b_parts) : s->b->data[0];
	while (s->b->size > 0 && stack_peek(s->b) != data->stop)
	{
		if (stack_peek(s->b) >= pivot)
			operate("pa", s->a, s->b, 0);
		if (!is_there_to_push(s, pivot, 'b'))
			break ;
		if (s->b->size > 0 && stack_peek(s->b) < pivot)
		{
			operate("rb", s->a, s->b, 0);
			(*r_count)++;
		}
	}
	return (0);
}

int	push_to_a(t_stacks *s, t_data *data, int pivot)
{
	int r_count;
	int possible_partition;

	if (!s->b->size)
		return (0);
	possible_partition = find_possible_partition(s, data, pivot);
	r_count = 0;
	if (a_push(s, data, pivot, &r_count))
		return (1);
	if (s->b->size > 0 && stack_peek(s->b) >= pivot)
		operate("pa", s->a, s->b, 0);
	if (s->b->size - r_count < s->b->size/2)
		while (s->b->size - r_count > 0 && s->b->size > 0)
		{
			operate("rb", s->a, s->b, 0);
			r_count++;
		}
	else
		while (r_count-- > 0 && s->b->size > 0)
			operate("rrb", s->a, s->b, 0);
	if (s->b->size > 0 && !is_in_stack(s->b, stack_peek(s->b_parts)))
		stack_pop(s->b_parts);
	if (!(data->error) && s->b->size > 0)
		t_stack_push(s->b_parts, possible_partition);
	return (1);
}

int	divide(t_stacks *s, t_data *data, char stack_name, int pivot)
{
	if (stack_name == 'a')
	{
		data->b_first = 1;
		push_to_b(s, data, pivot);
	}
	else
		push_to_a(s, data, pivot);
	return (1);
}
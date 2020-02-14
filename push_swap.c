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

int	sort_median(t_stack *s, int part_size)
{
	int *num = s->data;
	int	i;
	int j;

	i = s->size - part_size + 1;
	while (++i < s->size - 1)
	{
		j = s->size;
		while (--j > i)
		{
			if (num[j - 1] < num[j])
			{
				int temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}
}

int get_median(t_stack *s, int part_size)
{
	if (s->size)
		sort_median(s, part_size);
	return (!(s->size) ? 0 : s->data[part_size/2]);
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

int sort_3_b1(t_stacks *s, int bs, int *arr)
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
		return (sort_3_b2(s, bs, arr));
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
		return (sort_3_b1(s, s->b->size, s->b->data));
	return (0);
}

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
}

int sort_3_a(t_stacks *s, int part_size)
{
	if (part_size <= 1)
		return (0);
	if (part_size == 2 && stack_peek(s->a) > s->a->data[s->a->size - 2])
		operate("sa", s->a, s->b, 0);
	if (part_size == 3)
		return (sort_3_a1(s, s->a->size, s->a->data));
	return (0);
}

int find_possible_partition(t_stacks *s, t_data *data, int pivot)
{
	int p_size;
	int i;

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
	int p_size;
	int flag;
	int k;

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
}

static int	is_sorted(t_stack *s)
{
	int	i;

	i = -1;
	while (++i < s->size - 1)
		if (s->data[i] < s->data[i + 1])
			return (0);
	return (1);
}


int is_in_stack(t_stack *s, int k)
{
	int i;

	i = -1;
	while (++i < s->size)
		if (s->data[i] == k)
			return (1);
	return (0);
}

int handle_part_absense(t_stacks *s, int *a_part_size)
{
	if (((*a_part_size = part_size(s, 'a')) < 0)
		|| (!is_in_stack(s->b, stack_peek(s->b_parts)) && s->b->size))
	{
		if (*a_part_size < 0)
			stack_pop(s->a_parts);
		else
			stack_pop(s->b_parts);
		return (1);
	}
	return (0);
}

int test_sort(t_stacks *s)
{
	int a_part_size;
	int sorted;
	t_data data;

	while (!(sorted = is_sorted(s->a)) || (s->b->size))
	{
		if (handle_part_absense(s, &a_part_size))
			continue ;
		if (a_part_size <= 3 && !is_sorted(s->a))
		{
			sort_3_a(s, a_part_size);
			t_stack_push(s->a_parts, stack_peek(s->a));
			sorted = 1;
		}
		if (!sorted)
		{
			divide(s, &data, 'a', get_pivot(s, 'a'));
			continue ;
		}
		if (s->b->size)
			divide(s, &data, 'b', get_pivot(s, 'b'));
	}
}

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


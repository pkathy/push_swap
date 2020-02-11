#include "push_swap.h"


//part size or stack size if there is no parts
/*int	partition_size(t_stacks *s, t_data *data, char stack_name) {
	int i;
	if (stack_name == 'a' && !(data->is_a_parted))
		return (s->a->size);
	if (stack_name == 'b' && !(data->is_b_parted))
		return (s->b->size);
	if (stack_name == 'a')
	{
		i = s->a->size;
		while (--i >= 0)
			if (s->a->data[i] == data->next_part_a)
				return (s->a->size - i);
	}
	else
	{
		i = s->b->size;
		while (--i >= 0)
		{
			if (s->b->data[i] == data->next_part_b)
				return (s->b->size - i);
		}
	}
	return (-1);
}*/

int part_size1(t_stacks *s, char stack_name)
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

/*int	get_pivot(t_stacks *s, t_data *data, char stack_name)
{
	int	pivot;
	int i;

	pivot = 0;
	if (i = stack_name == 'a')
	{
		i = s->a->size;
		while (--i >= 0)
		{
			pivot += s->a->data[i];
			if (data->is_a_parted && s->a->data[i] == data->next_part_a)
				break;
		}
	}
	else
	{
		i = s->b->size;
		while (--i >= 0)
		{
			pivot += s->b->data[i];
			if (data->is_b_parted && s->b->data[i] == data->next_part_b)
				break;
		}
	}
	return (pivot/partition_size(s, data, stack_name));
}*/

int get_pivot1(t_stacks *s, char stack_name)
{
	int pivot;
	int i;

	pivot = 0;
	i = stack_name == 'a' ? s->a->size : s->b->size;
	if (stack_name == 'a')
		while (--i >= 0)
		{
			if (s->a_parts->size && s->a->data[i] == stack_peek(s->a_parts))
				break;
			pivot += s->a->data[i];
		}
	if (stack_name == 'b')
		while (--i >= 0)
		{
			pivot += s->b->data[i];
			if (s->b_parts->size && s->b->data[i] == stack_peek(s->b_parts))
				break;
		}
	return (pivot/part_size1(s, stack_name));
}

int find_possible_partition(t_stacks *s, t_data *data, int pivot)
{
	int part_size;
	int i;

	part_size = part_size1(s, 'b');
	i = s->b->size - part_size - 1;
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

int push_to_b1(t_stacks *s, t_data *data, int pivot)
{
	int	r_count;
	int stop;

	r_count = 0;
	if (!s->a->size)
		return (0);
	stop = s->a_parts->size ? stack_peek(s->a_parts) : s->a->data[0];
	while (stack_peek(s->a) != stop)
	{
		if (stack_peek(s->a) <= pivot)
		{
			if (data->b_first)
			{
				t_stack_push(s->b_parts, stack_peek(s->a));
				data->b_first = 0;
			}
			operate("pb", s->a, s->b);
		}
		if (s->a->data[s->a->size - 1] > pivot)
		{
			if (stack_peek(s->a) == stop)
				break ;
			operate("ra", s->a, s->b);
			r_count++;
		}
	}
	if (stack_peek(s->a) <= pivot)
		operate("pb", s->a, s->b);
	while (r_count-- > 0)
		operate("rra", s->a, s->b);
	if (s->a->size > 0 && !is_in_stack(s->a, stack_peek(s->a_parts)))
		stack_pop(s->a_parts);
}

int	push_to_a1(t_stacks *s, t_data *data, int pivot)
{
	int r_count;
	int stop;
	int possible_partition;

	if (!s->b->size)
		return (0);
	stop = s->b_parts->size ? stack_peek(s->b_parts) : s->b->data[0];
	possible_partition = find_possible_partition(s, data, pivot);
	r_count = 0;
	if (s->a->size)
		t_stack_push(s->a_parts, stack_peek(s->a));
	while (s->b->size > 0 && stack_peek(s->b) != stop)
	{
		if (stack_peek(s->b) >= pivot)
			operate("pa", s->a, s->b);
		if (s->b->size > 0 && stack_peek(s->b) < pivot)
		{
			operate("rb", s->a, s->b);
			r_count++;
		}
	}
	if (s->b->size > 0 && stack_peek(s->b) >= pivot)
		operate("pa", s->a, s->b);
	while (r_count-- > 0 && s->b->size > 0)
		operate("rrb", s->a, s->b);
	if (s->b->size > 0 && !is_in_stack(s->b, stack_peek(s->b_parts)))
		stack_pop(s->b_parts);
	if (!(data->error) && s->b->size > 0)
		t_stack_push(s->b_parts, possible_partition);
}

int	divide1(t_stacks *s, t_data *data, char stack_name, int pivot)
{
	if (stack_name == 'a')
	{
		data->b_first = 1;
		push_to_b1(s, data, pivot);
	}
	else
	{
		data->a_first = 1;
		push_to_a1(s,data, pivot);
	}
}

int	is_sorted(t_stack *s)
{
	int tmp;
	int	i;

	i = -1;
	while (++i < s->size - 1)
		if (s->data[i] < s->data[i + 1])
			return (0);
	return (1);
}

int	sort_three(t_stack *s, int part_size)
{
	int i;
	int j;
	int tmp;
	int *num = s->data;

	i = s->size - part_size;
	j = i + 1;

	for (int i = s->size - part_size; i < s->size - 1; i++)
	{
		for (int j = (s->size - 1); j > i; j--)
		{
			if (num[j - 1] < num[j])
			{
				int temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}

	printf(">>sorted<<\n");
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

int test_sort(t_stacks *s)
{
	int part_size;
	int sorted;
	t_data data;

	int pivot;
	while (!(sorted = is_sorted(s->a)) || (s->b->size))
	{
		if ((part_size = part_size1(s, 'a')) <0)
		{
			stack_pop(s->a_parts);
			continue ;
		}
		if (!is_in_stack(s->b, stack_peek(s->b_parts)) && s->b->size)
		{
			stack_pop(s->b_parts);
			continue ;
		}
		if (part_size <= 3)
		{
			if (!sorted)
				sort_three(s->a, part_size);
			t_stack_push(s->a_parts, stack_peek(s->a));
			sorted = 1;
		}
		if (!sorted)
		{
			pivot = get_pivot1(s, 'a');
			divide1(s, &data, 'a', get_pivot1(s, 'a'));
			continue ;
		}
		if (s->b->size)
		{
			pivot = get_pivot1(s, 'b');
			divide1(s, &data, 'b', get_pivot1(s, 'b'));
		}
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
	t_data	data;
	char *line;

	if (argc < 2)
		return (1);
	stack_from_source(&a, ++argv, argc - 1);
	stack_from_source(&b, 0, 0);
	stack_from_source(&b_parts, 0, 0);
	stack_from_source(&a_parts, 0, 0);

	s.a = &a;
	s.b = &b;
	s.a_parts = &a_parts;
	s.b_parts = &b_parts;
	data.is_b_parted = 0;
	data.is_a_parted = 0;
	data.level = 0;

	s.a = &a;
	s.b = &b;

	//data.next_part_b = find_first_partition(s.a, get_pivot1(&s,'a'));
	for (int i = 0; i < a.size; ++i)
		printf("%d ", a.data[i]);
	printf("\n");
	test_sort(&s);
	printf("a size: %ld\n", a.size);
	for (int i = 0; i < a.size; ++i)
		printf("%d ", a.data[i]);

	printf("\n");
	for (int i = 0; i < b.size; ++i)
		printf("%d ", b.data[i]);
	return (0);
}


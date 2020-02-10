#include "push_swap.h"


//part size or stack size if there is no parts
int	partition_size(t_stacks *s, t_data *data, char stack_name) {
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
}

int	get_pivot(t_stacks *s, t_data *data, char stack_name)
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
}
int	push_to_b(t_stacks *s, t_data *data, int pivot)
{
	int r_count;
	int stop;

	stop = s->a->data[s->a->size - partition_size(s, data, 'a')] ;
	r_count = 0;
	if (!s->a->size)
		return (0);
	while (s->a->data[s->a->size - 1] != stop)
	{
		if (s->a->data[s->a->size - 1] <= pivot)
		{
			operate("pb", s->a, s->b);
			if (data->b_first)
			{
				data->b_first = 0;
				data->next_part_b = s->b->data[s->b->size - 1];
				data->is_b_parted = 1;
			}
		}
		if (s->a->data[s->a->size - 1] > pivot)
		{
			if (s->a->data[s->a->size - 1] == stop)
				break ;
			operate("ra", s->a, s->b);
			r_count++;
		}
	}
	if (s->a->data[s->a->size - 1] <= pivot)
		operate("pb", s->a, s->b);
	while (r_count-- > 0)
		operate("rra", s->a, s->b);
	data->level++;
}

int find_possible_partition(t_stacks *s, t_data *data, int pivot)
{
	int part_size;
	int i;

	part_size = partition_size(s, data, 'b');
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
int	push_to_a(t_stacks *s, t_data *data, int pivot)
{
	int r_count;
	int stop;
	int possible_partition;

	stop = s->b->data[s->b->size - partition_size(s, data, 'b')];
	possible_partition = find_possible_partition(s, data, pivot);
	r_count = 0;
	if (!s->b->size)
		return (0);
	while (s->b->size > 0 && s->b->data[s->b->size - 1] != stop)
	{
		if (s->b->data[s->b->size - 1] >= pivot)
		{
			operate("pa", s->a, s->b);
			if (data->a_first)
			{
				data->a_first = 0;
				data->next_part_a = s->a->data[s->a->size - 1];
				data->is_a_parted = 1;
			}
		}
		if (s->b->size > 0 && s->b->data[s->b->size - 1] < pivot)
		{
			operate("rb", s->a, s->b);
			r_count++;
		}
	}
	if (s->b->size > 0 && s->b->data[s->b->size - 1] >= pivot)
		operate("pa", s->a, s->b);
	while (r_count-- > 0 && s->b->size > 0)
		operate("rrb", s->a, s->b);
	data->next_part_b = data->error ? data->next_part_b : possible_partition;
}

int	divide(t_stacks *s, t_data *data, char stack_name, int pivot)
{
	if (stack_name == 'a')
	{
		data->b_first = 1;
		push_to_b(s, data, pivot);
	}
	else
	{
		data->a_first = 1;
		push_to_a(s,data, pivot);
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

int	sort_three(t_stack *s, t_data *data, int part_size)
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

int find_first_partition(t_stack *a, int pivot)
{
	int i;

	i = a->size;
	while (--i >=0 )
		if (a->data[i] <= pivot)
			return (a->data[i]);
	return (0);
}

void debug(t_stacks *s)
{

	t_stack *a = s->a;
	t_stack *b = s->b;
	for (int i = 0; i < a->size; ++i)
		printf("%d ", a->data[i]);
	printf("\n");
	for (int i = 0; i < b->size; ++i)
		printf("%d ", b->data[i]);
}

int	sort(t_stacks *s, t_data data_prev, t_data data)
{
	int		pivot;
	int 	part_size;
	int 	sorted;
	t_data	data_new;

	if (!(data.is_b_parted))
		data_new = data_prev;
	else
		data_new = data;
	sorted = is_sorted(s->a);
	part_size = partition_size(s, &data_new, 'a');
	if (part_size <= 3)
	{
		if (!sorted)
			sort_three(s->a, &data_new, part_size);
		if (s->b->size)
		{
			pivot = get_pivot(s, &data_new, 'b');
			divide(s, &data_new, 'b', pivot);
			if (!is_in_stack(s->b, data_new.next_part_b))
			{
				if (data_new.level == data_prev.level)
					return (0);
				else if (is_in_stack(s->b, data_prev.next_part_b))
					data_new.next_part_b = data_prev.next_part_b;
				else
					return (0);
			}
			if (!sort(s, data, data_new) && data_new.level == data_prev.level)
				return (0);
			else
			{
				data_new.next_part_b = data_prev.next_part_b;
				data_new.level = data_prev.level;
				if (!sort(s, data, data_new))
					return (0);
			}
		}
		return (1);
	}
	if (!sorted)
	{
		pivot = get_pivot(s, &data_new, 'a');
		divide(s, &data_new, 'a', pivot);
		if (!sort(s, data, data_new)) {
			if (is_in_stack(s->b, data_prev.next_part_b)) {
				data_new.next_part_b = data_prev.next_part_b;
				data_new.level = data_prev.level;
				if (!sort(s, data, data_new))
					return (0);
			}
		}
	}
	else if (s->b->size)
	{
		pivot = get_pivot(s, &data_new, 'b');
		divide(s, &data_new, 'b', pivot);
		if (!is_in_stack(s->b, data_new.next_part_b))
		{
			if (data_new.level == data_prev.level)
				return (0);
			else if (is_in_stack(s->b, data_prev.next_part_b))
				data_new.next_part_b = data_prev.next_part_b;
			else
				return (0);
		}
		if (!sort(s, data, data_new) && data_new.level == data_prev.level)
			return (0);
		else
		{
			data_new.next_part_b = data_prev.next_part_b;
			data_new.level = data_prev.level;
			if (!sort(s, data, data_new))
				return (0);
		}
	}
	return (1);
}

//todo : make main greate again
int	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	t_stacks s;
	t_data	data;
	char *line;

	if (argc < 2)
		return (1);
	stack_from_source(&a, ++argv, argc - 1);
	stack_from_source(&b, 0, 0);

	data.is_b_parted = 0;
	data.is_a_parted = 0;
	data.level = 0;

	s.a = &a;
	s.b = &b;

	data.next_part_b = find_first_partition(s.a, get_pivot(&s, &data, 'a'));
	for (int i = 0; i < a.size; ++i)
		printf("%d ", a.data[i]);
	printf("\n");
	printf("part size :%d\n", partition_size(&s, &data, 'a'));
	sort(&s, data, data);
	//printf("%d\n", is_sorted(&a));
	for (int i = 0; i < a.size; ++i)
		printf("%d ", a.data[i]);
	printf("\n");
	for (int i = 0; i < b.size; ++i)
		printf("%d ", b.data[i]);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:55:21 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 19:55:23 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_stack *s)
{
	size_t	i;

	i = -1;
	while (s->data && ++i < s->size - 1)
		if (s->data[i] < s->data[i + 1])
			return (0);
	return (1);
}

int			is_in_stack(t_stack *s, int k)
{
	size_t	i;

	i = -1;
	while (++i < s->size)
		if (s->data[i] == k)
			return (1);
	return (0);
}

int			handle_part_absence(t_stacks *s, int *a_part_size)
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

int			test_sort(t_stacks *s)
{
	int		a_part_size;
	int		sorted;
	t_data	data;

	while (!(sorted = is_sorted(s->a)) || (s->b->size))
	{
		if (handle_part_absence(s, &a_part_size))
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
	return (1);
}

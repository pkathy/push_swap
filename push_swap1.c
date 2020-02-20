/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:04:47 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 20:04:48 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_3_a2_small(t_stacks *s, int as, int *arr)
{
	if (arr[as - 2] < arr[as - 1] && arr[as - 1] < arr[as - 3])
		operate("sa", s->a, s->b, 0);
	else if (arr[as - 2] < arr[as - 3] && arr[as - 3] < arr[as - 1])
	{
		operate("rra", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
	}
	else if (arr[as - 1] < arr[as - 3] && arr[as - 3] < arr[as - 2])
	{
		operate("sa", s->a, s->b, 0);
		operate("ra", s->a, s->b, 0);
	}
	return (0);
}

int	sort_3_a1_small(t_stacks *s, int as, int *arr)
{
	if (arr[as - 3] < arr[as - 2] && arr[as - 2] < arr[as - 1])
	{
		operate("sa", s->a, s->b, 0);
		operate("rra", s->a, s->b, 0);
	}
	else if (arr[as - 1] < arr[as - 2] && arr[as - 2] < arr[as - 3])
		return (0);
	else if (arr[as - 3] < arr[as - 1] && arr[as - 1] < arr[as - 2])
		operate("rra", s->a, s->b, 0);
	else
		return (sort_3_a2_small(s, as, arr));
	return (0);
}

int	sort_small(t_stacks *s, int part_size)
{
	if (part_size <= 1)
		return (0);
	if (part_size == 2 && stack_peek(s->a) > s->a->data[s->a->size - 2])
		operate("sa", s->a, s->b, 0);
	if (part_size == 3)
		sort_3_a1_small(s, s->a->size, s->a->data);
	return (0);
}

int	find_min(t_stack *s)
{
	long	min;
	size_t	i;

	min = 2147483648;
	i = -1;
	while (++i < s->size)
	{
		if (s->data[i] < min)
			min = s->data[i];
	}
	return (min);
}

int	ra_or_rra(t_stack *s, int a)
{
	size_t i;

	i = -1;
	while (s->data[++i] != a)
		continue ;
	if (i <= s->size / 2)
		return (0);
	else
		return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:55:05 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 19:55:07 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			sort_medium(t_stacks *s, int part_size)
{
	int min;
	int t;

	if (part_size <= 3)
	{
		sort_small(s, part_size);
		operate("pa", s->a, s->b, 0);
		operate("pa", s->a, s->b, 0);
		return (0);
	}
	min = find_min(s->a);
	t = ra_or_rra(s->a, min);
	while (stack_peek(s->a) != min)
		operate(t ? "ra" : "rra", s->a, s->b, 0);
	operate("pb", s->a, s->b, 0);
	return (sort_medium(s, part_size - 1));
}

static int	is_sorted(t_stack *s)
{
	size_t	i;

	i = -1;
	while (++i < s->size - 1)
		if (s->data[i] < s->data[i + 1])
			return (0);
	return (1);
}

int			free_stacks(t_stacks *s)
{
	if (s->a->data)
		free(s->a->data);
	if (s->b->data)
		free(s->b->data);
	if (s->a_parts->data)
		free(s->a_parts->data);
	if (s->b_parts->data)
		free(s->b_parts->data);
	return (1);
}

t_stacks	init_stacks(t_stack *a, t_stack *b, t_stack *a_parts,
		t_stack *b_parts)
{
	t_stacks s;

	s.b = b;
	s.a = a;
	s.a_parts = a_parts;
	s.b_parts = b_parts;
	return (s);
}

int			main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;
	t_stack		b_parts;
	t_stack		a_parts;
	t_stacks	s;

	if (argc < 2)
		return (1);
	if (!stack_from_source(&a, ++argv, argc - 1))
	{
		ft_printf("Error\n");
		return (0);
	}
	stack_from_source(&b, 0, 0);
	stack_from_source(&b_parts, 0, 0);
	stack_from_source(&a_parts, 0, 0);
	s = init_stacks(&a, &b, &a_parts, &b_parts);
	if (!is_sorted(&a) && a.size <= 5 && a.size > 3)
		sort_medium(&s, a.size);
	else
		test_sort(&s);
	free_stacks(&s);
	return (0);
}

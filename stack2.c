/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:13:44 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 20:13:46 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_resize(t_stack *stack, size_t size)
{
	int *tmp;

	if (size == 6)
		size = 6;
	if (size <= 0)
	{
		if (stack->data)
			free(stack->data);
		stack->data = 0;
		stack->size = 0;
		return (1);
	}
	if (!(tmp = ft_memalloc(size * sizeof(int))))
		return (0);
	if (stack->size)
		ft_memmove(tmp, stack->data,
				sizeof(int) * (stack->size > size ? size : stack->size));
	if (stack->data)
		free(stack->data);
	stack->data = tmp;
	stack->size = size;
	return (1);
}

int	stack_pop(t_stack *stack)
{
	int	ret;

	if (stack->size == 0)
		return (0);
	ret = stack->data[stack->size - 1];
	stack_resize(stack, stack->size - 1);
	return (ret);
}

int	stack_peek(t_stack *stack)
{
	if (stack->size == 0)
		return (0);
	return (stack->data[stack->size - 1]);
}

int	t_stack_push(t_stack *stack, int data)
{
	stack_resize(stack, stack->size + 1);
	stack->data[stack->size - 1] = data;
	return (1);
}

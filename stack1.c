/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:45:14 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 19:45:15 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_valid(char *str)
{
	int c;

	c = 0;
	if ((*str == '-' || *str == '+') && *(str + 1))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) || c > 10)
			return (0);
		str++;
		c++;
	}
	return (1);
}

static int	is_duplicate(int *arr, int arr_size, int new)
{
	int	i;

	i = 0;
	while (i < arr_size)
		if (new == arr[i++])
			return (1);
	return (0);
}

static int	handle_error(int *p)
{
	free(p);
	return (0);
}

int			handle_one_arg(t_stack *stack, char *src)
{
	size_t		source_size;
	int			i;
	long		tmp;
	char		**source;

	i = 0;
	if (!init_one_arg(&source, &source_size, src, stack))
		return (0);
	if (!(stack->data = ft_memalloc(source_size * sizeof(int))))
		return (0);
	ft_memmove(source + 1, source, source_size * sizeof(char *));
	while ((source[0] = 0) == 0 && source[source_size])
	{
		if (!is_valid(source[source_size]))
			return (handle_error(stack->data));
		tmp = ft_atol(source[source_size]);
		if ((long)tmp != (int)tmp || is_duplicate(stack->data, i, tmp))
			return (handle_error(stack->data));
		stack->data[i++] = tmp;
		free(source[source_size]);
		source_size--;
	}
	free(source[0]);
	free(source);
	return (1);
}

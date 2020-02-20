/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:56:30 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 19:56:31 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		is_space(char c)
{
	if (c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int		is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

long			ft_atol(const char *str)
{
	int				sign;
	long long		n;

	n = 0;
	sign = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (is_digit(*str))
	{
		n = n * 10 + *str++ - '0';
	}
	if (sign)
		return (-n);
	return (n);
}

static int		arr_len(char **arr, size_t *len)
{
	size_t i;

	i = 0;
	while (arr[i])
		i++;
	*len = i;
	return (1);
}

int				init_one_arg(char ***source,
		size_t *source_size, char *src, t_stack *stack)
{
	if (!(*source = ft_strsplit(src, ' ')))
		return (0);
	arr_len(*source, source_size);
	stack->size = *source_size;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:54:45 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 19:54:48 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_median(t_stack *s, int part_size)
{
	int		*num;
	size_t	i;
	size_t	j;
	int		temp;

	num = s->data;
	i = s->size - part_size + 1;
	while (++i < s->size - 1)
	{
		j = s->size;
		while (--j > i)
		{
			if (num[j - 1] < num[j])
			{
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}
	return (0);
}

int	get_median(t_stack *s, int part_size)
{
	int ret;

	if (s->size)
		sort_median(s, part_size);
	ret = !(s->size) ? 0 : s->data[part_size / 2];
	free(s->data);
	return (ret);
}

#include "push_swap.h"

int	sort_median(t_stack *s, int part_size)
{
	int		*num;
	size_t	i;
	size_t	j;

	num = s->data;
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
	return (0);
}

int get_median(t_stack *s, int part_size)
{
	if (s->size)
		sort_median(s, part_size);
	return (!(s->size) ? 0 : s->data[part_size/2]);
}

#include "push_swap.h"

int	stack_swap(t_stack *s)
{
	int tmp;

	if (s->size < 2)
		return (1);
	tmp = s->data[s->size - 1];
	s->data[s->size - 1] = s->data[s->size - 2];
	s->data[s->size - 2] = tmp;
	return (1);
}

int	stack_push(t_stack *from, t_stack *to)
{
	if (!from)
		return (0);
	if (!from->data || !from->size)
		return (1);
	if (!stack_resize(to, to->size + 1))
		return (0);
	to->data[to->size - 1] = from->data[from->size - 1];
	if (!(stack_resize(from, from->size - 1)))
		return (0);
	return (1);
}


void	stack_rotate(t_stack *s, int direction)
{
	int tmp;

	if (!s || !(s->data) || s->size == 1)
		return ;
	if (!direction)
	{
		tmp = s->data[s->size - 1];
		ft_memmove(s->data + 1, s->data, sizeof(int) * (s->size - 1));
		s->data[0] = tmp;
	}
	else
	{
		tmp = s->data[0];
		ft_memmove(s->data, s->data + 1, sizeof(int) * (s->size - 1));
		s->data[s->size - 1] = tmp;
	}
}

int		operate1(char *operation, t_stack *a, t_stack *b)
{
	if ((ft_strequ("rr", operation)))
	{
		stack_rotate(a, 0);
		stack_rotate(b, 0);
		return (1);
	}
	else if ((ft_strequ("rra", operation)))
	{
		stack_rotate(a, 1);
		return (1);
	}
	else if ((ft_strequ("rrb", operation)))
	{
		stack_rotate(b, 1);
		return (1);
	}
	else if ((ft_strequ("rrr", operation)))
	{
		stack_rotate(a, 1);
		stack_rotate(b, 1);
		return (1);
	}
	return (0);
}

int		operate(char *operation, t_stack *a, t_stack *b)
{
	static int c;
	//if (!ft_strequ(operation, "rrb"))
	c++;
	printf("%s, %d\n", operation, c);
	//if (a->size && b->size)
	//	printf("a top: %d, b top: %d\n", a->data[a->size - 1], b->data[b->size - 1]);
	if (ft_strequ("sa", operation))
		return (stack_swap(a));
	else if (ft_strequ("sb", operation))
		return (stack_swap(b));
	else if (ft_strequ("ss", operation))
		return (stack_swap(b) * stack_swap(a));
	else if (ft_strequ("pa", operation))
		return(stack_push(b, a));
	else if ((ft_strequ("pb", operation)))
		return(stack_push(a, b));
	else if ((ft_strequ("ra", operation)))
	{
		stack_rotate(a, 0);
		return (1);
	}
	else if ((ft_strequ("rb", operation)))
	{
		stack_rotate(b, 0);
		return (1);
	}
	else
		return (operate1(operation, a, b));
}
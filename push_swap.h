/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:25:13 by pkathy            #+#    #+#             */
/*   Updated: 2020/02/20 20:25:14 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"

typedef struct	s_stack {
	int		*data;
	size_t	size;
}				t_stack;

typedef struct	s_two {
	t_stack	*a;
	t_stack	*b;
	t_stack *a_parts;
	t_stack	*b_parts;
}				t_stacks;

typedef struct	s_data {

	int b_first;
	int error;
	int stop;
	int bps;
}				t_data;

int				stack_resize(t_stack *stack, size_t size);
int				stack_push(t_stack *from, t_stack *to);
int				stack_from_source(t_stack *stack,
				char **source, size_t source_size);
int				stack_resize(t_stack *stack, size_t size);
int				stack_pop(t_stack *stack);
int				t_stack_push(t_stack *stack, int data);
int				stack_peek(t_stack *stack);
int				operate(char *operation, t_stack *a, t_stack *b, int mode);
int				is_in_stack(t_stack *s, int k);
int				get_median(t_stack *s, int part_size);
int				sort_3_a(t_stacks *s, int part_size);
int				sort_3_b(t_stacks *s, int part_size);
int				divide(t_stacks *s, t_data *data, char stack_name, int pivot);
int				part_size(t_stacks *s, char stack_name);
int				get_pivot(t_stacks *s, char stack_name);
int				find_possible_partition(t_stacks *s, t_data *data, int pivot);
int				is_there_to_push(t_stacks *s, int pivot, char stack);
int				test_sort(t_stacks *s);
int				sort_small(t_stacks *s, int part_size);
long			ft_atol(const char *str);
int				handle_one_arg(t_stack *stack, char *src);
int				init_one_arg(char ***source, size_t *source_size, char *src,
				t_stack *stack);
int				sort_3_a2_small(t_stacks *s, int as, int *arr);
int				sort_3_a1_small(t_stacks *s, int as, int *arr);
int				find_min(t_stack *s);
int				ra_or_rra(t_stack *s, int a);
#endif

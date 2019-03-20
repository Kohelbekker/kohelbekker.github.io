/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:33:15 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:33:17 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector		v_multi(double a, t_vector b)
{
	t_vector	tmp;

	tmp = (t_vector){a, a, a};
	return (tmp * b);
}

double			v_length(t_vector a)
{
	return (sqrt((double)(a[0] * a[0] + a[1] * a[1] + a[2] * a[2])));
}

t_vector		unit_vector(t_vector b)
{
	return (v_div(v_length(b), b));
}

t_vector		point_vector(double f, t_ray *ray)
{
	t_vector	i;

	i = v_multi(f, ray->b);
	return (ray->a + i);
}

double			dot(t_vector a, t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

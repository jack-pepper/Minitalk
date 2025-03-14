/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:33:51 by mmalie            #+#    #+#             */
/*   Updated: 2024/11/14 09:28:04 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/* 
 * Implementation of isalnum() from <ctype.h>: Checks if the given character 
 * is alphanumeric (either a letter or a digit).
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

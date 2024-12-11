/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:28 by mmalie            #+#    #+#             */
/*   Updated: 2024/11/14 09:34:23 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

void	ft_show_bin(int num, unsigned int nb_of_bytes);
int		ft_is_bit_set(unsigned int num, int bit_pos);
int		ft_encrypt_char(int target_pid, int character);

// Must improve input checking! types must match
int	main(int argc, char **argv)
{
	char		*msg;
	sigset_t	sigset;
	int			target_pid;
	int			i;

	i = 0;
	msg = NULL;
	if (argc != 3)
	{
		ft_putstr_fd("Error: invalid parameters\n", 2);
	}
	else
	{
		target_pid = ft_atoi(argv[1]);
		msg = argv[2];
		sigemptyset(&sigset);
		sigaddset(&sigset, SIGUSR1);
		sigaddset(&sigset, SIGUSR2);
		while (msg[i] != '\0')
		{
			if (ft_encrypt_char(target_pid, msg[i]) == -1)
				return (-1);
			//else
			//	ft_printf("\nChar '%c' successfully encrypted!\n", msg[i]);
			i++;
		}
		return (0);
	}
}

void	ft_show_bin(int num, unsigned int nb_of_bytes)
{
	unsigned int		size;
	int					i;

	size = sizeof(num) * 8;
	if (nb_of_bytes > size)
		nb_of_bytes = size ;
	i = size - 1;
	while (i >= (int)(size - nb_of_bytes))
	{
		ft_printf("%d", (num >> i) & 1);
		i--;
	}
}

int	ft_is_bit_set(unsigned int num, int bit_pos)
{
	int	is_set;

	is_set = 0;
	if (bit_pos < 0 || ((unsigned int)bit_pos >= (sizeof(num) * 8)))
		return (-1);
	if (num & (1 << bit_pos))
		is_set = 1;
	return (is_set);
}

int	ft_encrypt_char(int target_pid, int character)
{
	int	res;
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (ft_is_bit_set(character, i) == 0)
		{
			res = kill(target_pid, SIGUSR1);
			//if (res == 0)
			//	ft_putchar_fd('0', 1);
		}
		else if (ft_is_bit_set(character, i) == 1)
		{
			res = kill(target_pid, SIGUSR2);
			//if (res == 0)
			//	ft_putchar_fd('1', 1);
		}
		if (res != 0)
			return (-1);
		usleep(500);
		i--;
	}
	return (0);
}

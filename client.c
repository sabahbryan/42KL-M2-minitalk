/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:48:04 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/17 16:48:12 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(pid_t server_pid, char c, int bit)
{
	if (bit < 0)
		return ;
	if (c & (1 << bit))
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(100);
	send_bit(server_pid, c, bit - 1);
}

void	send_char(pid_t server_pid, char c)
{
	send_bit(server_pid, c, 7);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid = ft_atoi(argv[1]);
	char	*message = argv[2];

	if (argc != 3)
	{
		ft_printf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	while (*message)
		send_char(server_pid, *message++);
	return (0);
}

// Error: DECL_ASSIGN_LINE     (line:  34, col:  24):	Declaration and assignation on a single line
// Error: DECL_ASSIGN_LINE     (line:  35, col:  22):	Declaration and assignation on a single line
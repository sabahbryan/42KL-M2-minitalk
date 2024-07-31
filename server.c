/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:49:27 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/17 16:49:29 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// 		byte |= (1 << bit);

/**
 * @brief	handles incoming signals and reconstructs the received characters
 * @param	signum	signal number received by handlers SIGUSR1 or SIGUSR2
 * @var		bit		keeps track of the current bit being processed
 * @var		byte	accumulates the bits to form a complete byte
 * @return	none.
 */
void	handle_signal(int signum)
{
	static int	bit = 0;
	static int	byte = 0;

	if (signum == SIGUSR1)
		byte |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (byte == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", byte);
		bit = 0;
		byte = 0;
	}
}

/**
 * @brief	entry point of the server program
 * @param	none
 * @var		pid		server process ID
 * @var		sa		structure used to define the signal handling behavior
 * @return	enters infinite loop using 'pause' to wait for signals
 */
int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

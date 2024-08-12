/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:45:55 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/26 21:46:17 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
// (1 << (7 - bit)): if the signal received is SIGUSR1, it indicates binary "1"
//					 corresponding bit is set in the byte
// SIGUSR2 implicitly indicates binary "0" (default state)
// when (bit == 8), a complete byte (character) has been received
// prints newline at end of message (byte == '\0')
// otherwise prints the character represented by byte using ft_printf
// reset "bit" and "byte" to 0 for receiving the next character
// BITS
// (1 << (7 - bit)): correct, first bit is set to MSB (7th), move towards LSB.
//					 aligns with the order sent by the client.
//					 reads from left to right.
// (1 << bit): incorrect, first bit is set to LSB (0th), move towards MSB
//					 reversed order from what was sent by the client.
//					 reads from right to left.

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
// retrieve the server's PID
// prints the PID to the console for the client to see
// sa.sa_handler: sets handle_signal as the function to handle incoming signals
// sa.sa_flags: automatically restarts interrupted system calls
// sigemptyset: initializes signal set to exclude all signals during the
//				execution of the signal handler
// sigaction: register handle_signal as the handler for SIGUSR1 and SIGUSR2
// pause: 1) puts the server in an infinite loop to wait for signals
//		  2) server remains idle until a signal is received, triggering the
//			 signal handler

/*NEW
void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	byte = 0;
	//pid_t	client_pid;

	(void)context;
	//client_pid = info->si_pid;
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
		kill(info->si_pid, SIGUSR2);
	}
}
//kill(client_pid, SIGUSR1);
//exit(EXIT_SUCCESS);

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
*/

/*OLD
void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	byte = 0;
	pid_t		client_pid = info->si_pid;

	(void)context;
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
	kill(client_pid, SIGUSR1);
}

// void	handle_signal(int signum, siginfo_t *info, void *context)
// {
// 	static int	bit = 0;
// 	static int	byte = 0;

// 	(void)context;
// 	if (signum == SIGUSR1)
// 		byte |= (1 << (7 - bit));
// 	bit++;
// 	if (bit == 8)
// 	{
// 		if (byte == '\0')
// 			ft_printf("\n");
// 		else
// 			ft_printf("%c", byte);
// 		bit = 0;
// 		byte = 0;
// 		kill(info->si_pid, SIGUSR1);
// 	}
// }

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
*/
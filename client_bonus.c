/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:45:42 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/26 21:45:47 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * @brief	sends a single bit to the server
 * @param	server_pid	process ID of the server
 * @param	c			character to send
 * @param	bit			current bit (from 7 to 0) position to send
 * @return	none. recursively calls itself until all signals are sent
 */
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

/**
 * @brief	sends character to the server
 * @param	server_pid	process ID of the server
 * @param	c			character to send
 * @return	none.
 */
void	send_char(pid_t server_pid, char c)
{
	send_bit(server_pid, c, 7);
}

/**
 * @brief	checks if the string consists only of digit characters
 * @param	str	string to check for digits
 * @var		i	loop counter to iterate over the string
 * @return	returns true if all characters are digits
 */
int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	entry point of client program
 * @param	argc		number of command-line arguments
 * @param	argv		array of command-line arguments
 * @var		server_pid	process ID of the server
 * @var		message		messsage string to be sent
 * @return	returns 0 upon successful execution, 1 for error
 */
int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3 || !is_digit_str(argv[1]))
	{
		ft_putstr_fd("Error! Correct format: ./client <pid> <message>\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
		send_char(server_pid, *message++);
	send_char(server_pid, '\0');
	return (0);
}

/*NEW2
void	ft_confirm(int signal)
{
	if (signal == SIGUSR1 || signal == SIGUSR2)
		ft_printf("Message acknowledged by server.\n");
}
//if (signal == SIGUSR1)

void	send_bit(pid_t server_pid, char c, int bit)
{
	if (bit < 0)
		return ;
	if (c & (1 << bit))
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(100);
	pause();
	send_bit(server_pid, c, bit - 1);
}

void	send_char(pid_t server_pid, char c)
{
	send_bit(server_pid, c, 7);
}

int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3 || !is_digit_str(argv[1]))
	{
		ft_putstr_fd("Correct format: ./client_bonus <pid> <message>\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	//signal(SIGUSR1, ft_confirm);

	struct sigaction sa_ack;
	sa_ack.sa_handler = ft_confirm;
	sigemptyset(&sa_ack.sa_mask);
	sa_ack.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa_ack, NULL);

	while (*message)
		send_char(server_pid, *message++);
	send_char(server_pid, '\0');
	return (0);
}

	// struct sigaction sa_ack;
	// sa_ack.sa_handler = ft_confirm;
	// sigemptyset(&sa_ack.sa_mask);
	// sa_ack.sa_flags = SA_RESTART;
	// sigaction(SIGUSR2, &sa_ack, NULL); // Handle SIGUSR2 as acknowledgment
	// while (*message)
	// 	send_char(server_pid, *message++);
	// send_char(server_pid, '\0');
	// return (0);

//acknowledge?
//ft_printf("String received by PID: %i\n", i->si_pid);
*/

/*OLD
volatile	sig_atomic_t	g_acknowledged = 0;

void	handle_ack(int signum)
{
	(void)signum;
	ft_printf("Message acknowledged by server.\n");
	g_acknowledged = 1;
}

void	send_bit(pid_t server_pid, char c, int bit)
{
	if (bit < 0)
		return ;
	if (c & (1 << bit))
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(100);
	pause();
	send_bit(server_pid, c, bit - 1);
}

void	send_char(pid_t server_pid, char c)
{
	send_bit(server_pid, c, 7);
}

int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3 || !is_digit_str(argv[1]))
	{
		ft_putstr_fd("Error! Correct format: ./client <pid> <message>\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];

	struct	sigaction sa_ack;
	sa_ack.sa_handler = handle_ack;
	sigemptyset(&sa_ack.sa_mask);
	sa_ack.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_ack, NULL);
	while (*message)
	{
		g_acknowledged = 0;
		send_char(server_pid, *message++);
		while (!g_acknowledged)
			pause();
	}
	g_acknowledged = 0;
	send_char(server_pid, '\0');
	while (!g_acknowledged)
		pause();
	return (0);
}
*/
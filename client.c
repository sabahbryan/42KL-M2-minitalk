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
// if (bit < 0), function returns, ending the recursion
// bitwise ops: checks if the current bit  in the character c is set (1)
// if bit is set, sends SIGUSR1 to the server, otherwise sends SIGUSR2
// usleep call introduces a short delay of 100 microsecond
// function repeatedly calls itself with the next remaining lower bit

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
// initiates the process of sending a character to the server
// calls send_bit with the highest bit index (7)

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
// checks if a given string consists entirely of digits
// verify that the first argument is valid (server PID)
// returns 0 if the string is NULL or contains non-digit characters
// returns 1, indicates valid numeric PID in string

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
// checks for the correct number of arguments (3)
// checks if the first argument (server PID) is a number using is_digit_str
// error handling: if checks fail, error message is printed to stderr and
//				   the program exits with a non-zero status
// ft_atoi: converts the server PID argument to an integer
// assigns the message string to the argv[2]
// loops through each character in the message, calls send_char to send each
// character to the server
// sends "\0" to indicate the end of the message, then returns 0
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

void	handle_signal(int signum)
{
	static int	bit = 0;
	static int	byte = 0;

	if (signum == SIGUSR1)
		byte |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", byte);
		fflush(stdout);
		bit = 0;
		byte = 0;
	}
}

int	main()
{
	pid_t	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}

// Error: NO_ARGS_VOID         (line:  32, col:  10):	Empty function argument requires void
// Error: DECL_ASSIGN_LINE     (line:  34, col:  17):	Declaration and assignation on a single line
// Error: NL_AFTER_VAR_DECL    (line:  35, col:   1):	Variable declarations must be followed by a newline
// Error: VAR_DECL_START_FUNC  (line:  36, col:   1):	Variable declaration not at start of function
// Error: SPACE_REPLACE_TAB    (line:  36, col:  21):	Found space when expecting tab
// Error: MISALIGNED_VAR_DECL  (line:  36, col:  22):	Misaligned variable declaration
// Error: TOO_FEW_TAB          (line:  40, col:   1):	Missing tabs for indent level
// Error: SPACE_REPLACE_TAB    (line:  40, col:   5):	Found space when expecting tab
// Error: TOO_FEW_TAB          (line:  41, col:   1):	Missing tabs for indent level
// Error: SPACE_REPLACE_TAB    (line:  41, col:   5):	Found space when expecting tab
// Error: EMPTY_LINE_FUNCTION  (line:  42, col:   1):	Empty line in function
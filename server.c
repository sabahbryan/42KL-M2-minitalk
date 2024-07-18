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

#include "server.h"

// server.c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signum)
{
    static int bit = 0;
    static int byte = 0;

    if (signum == SIGUSR1)
        byte |= (1 << bit);
    bit++;
    if (bit == 8) {
        printf("%c", byte);
        fflush(stdout);
        bit = 0;
        byte = 0;
    }
}

int main()
{
    printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause(); // Wait for signals

    return 0;
}

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

#include "client.h"

// client.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void send_bit(pid_t server_pid, char c, int bit)
{
    if (bit < 0) return;

    if (c & (1 << bit))
        kill(server_pid, SIGUSR1);
    else
        kill(server_pid, SIGUSR2);

    usleep(100); // Small delay to ensure signals are processed

    send_bit(server_pid, c, bit - 1); // Recursively send the next bit
}

void send_char(pid_t server_pid, char c)
{
    send_bit(server_pid, c, 7); // Start sending from the most significant bit
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    while (*message)
        send_char(server_pid, *message++);

    return 0;
}

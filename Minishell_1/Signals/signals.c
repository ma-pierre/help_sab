/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:04:02 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 22:33:11 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	//if (signum == SIGQUIT)
		//return ;
}

void	init_signals(void)
{
	struct sigaction	s_signals;

	s_signals.sa_sigaction = &signal_handler;
	s_signals.sa_flags = 0;
	sigemptyset(&s_signals.sa_mask);
	sigaddset(&s_signals.sa_mask, SIGINT);
	sigaddset(&s_signals.sa_mask, SIGQUIT);
	sigaction(SIGINT, &s_signals, NULL);
	sigaction(SIGQUIT, &s_signals, NULL);
}

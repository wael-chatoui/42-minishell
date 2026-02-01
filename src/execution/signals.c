/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:39:45 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	sig_handler_child(int sig)
{
	(void)sig;
}

void	sig_int_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** Sets up signals for child processes (default behavior)
*/
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
** Sets up signals for the parent process (interactive shell)
*/
void	setup_parent_signals(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

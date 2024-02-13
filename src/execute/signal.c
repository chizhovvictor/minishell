/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:05:18 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:33:31 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	g_err_no = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	signal_handler_sigint(int signal)
{
	(void)signal;
	g_err_no = 1;
	write(1, "\n", 1);
}

void	signal_hendler_sigquit(int signal)
{
	(void)signal;
	g_err_no = 130;
	ft_putstr_fd("Quit: 3\n", 2);
}

void	define_signals(void)
{
	signal(SIGINT, signal_handler_sigint);
	signal(SIGQUIT, signal_hendler_sigquit);
}

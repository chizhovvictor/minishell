/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:59:51 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 15:30:03 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void) argv;
	g_err_no = 0;
	if (argc > 1)
		exit(1);
	shell = create_shell();
	welcome_message();
	shell->envp = envp;
	shell->env = add_env(envp);
	rl_catch_signals = 0;
	while (1)
	{
		parse_readline(shell);
		if (has_pipes(shell))
		{
			create_pipe_list(shell);
			if (shell->cant_execute == 0)
				execute_pipes(shell);
		}
		else
			command_func(shell, envp);
		clean_array(shell);
	}
}

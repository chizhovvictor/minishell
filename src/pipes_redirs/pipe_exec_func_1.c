/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_func_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:40:38 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:40:40 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command_in_pipe(t_pipe *pipe)
{
	int				pid;
	t_parser_token	**token_key;

	token_key = (t_parser_token **) pipe->commands->array;
	if (has_redir(pipe->commands))
	{
		pid = fork();
		if (pid == 0)
			command_func2(token_key, pipe->commands,
				pipe->shell, pipe->shell->envp);
		waitpid(pid, &g_err_no, 0);
		g_err_no /= 256;
		return ;
	}
	else
		if (!command_func3(token_key, pipe->commands,
				pipe->shell, pipe->shell->envp))
			return ;
}

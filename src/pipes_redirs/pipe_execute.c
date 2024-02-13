/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:40:50 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:40:51 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipes(t_shell *shell)
{
	int		i;
	int		fd_array[1000][2];
	t_pipe	**pipes;

	i = 0;
	pipes = (t_pipe **) shell->pipe_array->array;
	while (i < shell->pipe_array->size - 1)
	{
		pipe(fd_array[i]);
		i++;
	}
	i = 0;
	while (i < shell->pipe_array->size)
	{
		execute_pipe(pipes[i], i, fd_array, shell->pipe_array->size);
		i++;
	}
	close_pipes(shell->pipe_array->size - 1, fd_array);
	find_last_err(shell);
}

void	find_last_err(t_shell *shell)
{
	int		i;
	t_pipe	**pipes;

	i = 0;
	pipes = (t_pipe **) shell->pipe_array->array;
	while (i < shell->pipe_array->size)
	{
		if (pipes[i]->last_pipe)
			waitpid(pipes[i]->pid, &g_err_no, 0);
		else
			waitpid(pipes[i]->pid, 0, 0);
		i++;
	}
	if (g_err_no == 256)
		g_err_no = 1;
	else
		g_err_no /= 256;
}

int	heredoc_in_pipe(t_array_list *parser_array, t_shell *shell)
{
	t_parser_token	**token_key;
	int				i;
	int				heredocced;

	heredocced = 0;
	i = 0;
	token_key = (t_parser_token **) parser_array->array;
	while (i < parser_array->size)
	{
		if (token_key[i]->main_type == HEREDOC)
		{
			if (parser_array->size == 1)
				shell->only_redir = 1;
			i = redir_heredoc(parser_array, i, shell);
			heredocced = 1;
		}
		else
			i++;
	}
	return (heredocced);
}

void	execute_pipe(t_pipe *pipe_token, int i, int fd_array[1000][2], int size)
{
	int	heredocced;

	pipe_token->pid = fork();
	if (pipe_token->pid == 0)
	{
		heredocced = heredoc_in_pipe(pipe_token->commands, pipe_token->shell);
		if (pipe_token->shell->only_redir)
			exit(g_err_no);
		do_pipe_redirects(pipe_token, fd_array, i, heredocced);
		close_pipes(size - 1, fd_array);
		execute_command_in_pipe(pipe_token);
		exit(g_err_no);
	}
}

void	do_pipe_redirects(t_pipe *pipe_token, int fd_array[1000][2],
				int i, int heredocced)
{
	if (pipe_token->first_pipe)
	{
		dup2(fd_array[i][1], STDOUT_FILENO);
		close(fd_array[i][1]);
	}
	else if (pipe_token->middle_pipe)
	{
		if (!heredocced)
			dup2(fd_array[i - 1][0], STDIN_FILENO);
		dup2(fd_array[i][1], STDOUT_FILENO);
		close(fd_array[i - 1][0]);
		close(fd_array[i][1]);
	}
	else if (pipe_token->last_pipe)
	{
		if (!heredocced)
			dup2(fd_array[i - 1][0], STDIN_FILENO);
		close(fd_array[i - 1][0]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:41:06 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:41:08 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_pipes(t_shell *shell)
{
	int				i;
	t_parser_token	**parser_tokens;

	i = 0;
	parser_tokens = (t_parser_token **) shell->parser_tokens_array->array;
	count_pipes(shell);
	while (i < shell->parser_tokens_array->size)
	{
		if (parser_tokens[i]->main_type == PIPELINE)
			return (1);
		i++;
	}
	return (0);
}

void	count_pipes(t_shell *shell)
{
	int				i;
	t_parser_token	**parser_tokens;

	i = 0;
	parser_tokens = (t_parser_token **) shell->parser_tokens_array->array;
	while (i < shell->parser_tokens_array->size)
	{
		if (parser_tokens[i]->main_type == PIPELINE)
			shell->number_of_pipes++;
		i++;
	}
}

int	is_redir(t_parser_token *token)
{
	if (token->main_type == REDIRECT_APPEND_OUTPUT
		|| token->main_type == REDIRECT_OUTPUT
		|| token->main_type == REDIRECT_INPUT || token->main_type == HEREDOC)
		return (1);
	return (0);
}

void	add_flags(t_pipe *pipe, t_parser_token *token)
{
	if (pipe->is_redir == 1)
		return ;
	if (pipe->is_builtin == 1 || pipe->is_execve == 1)
		return ;
	if (is_redir(token))
		pipe->is_redir = 1;
	else if (token->main_type == BIlD_IN)
		pipe->is_builtin = 1;
	else if (token->main_type == EXECUTABLE
		|| token->main_type == EXECUTABLE_PATH)
		pipe->is_execve = 1;
}

t_pipe	*init_pipe(t_shell *shell)
{
	t_pipe	*pipe_token;

	pipe_token = malloc(sizeof(t_pipe));
	pipe_token->commands = create_array_list();
	pipe_token->shell = shell;
	pipe_token->first_pipe = 0;
	pipe_token->middle_pipe = 0;
	pipe_token->last_pipe = 0;
	pipe_token->is_redir = 0;
	pipe_token->is_builtin = 0;
	pipe_token->is_execve = 0;
	return (pipe_token);
}

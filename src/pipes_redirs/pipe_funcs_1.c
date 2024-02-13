/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_funcs_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:40:58 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:41:00 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_last_command(t_shell *shell, int index)
{
	t_parser_token	**parser_tokens;
	t_pipe			*pipe;

	parser_tokens = (t_parser_token **) shell->parser_tokens_array->array;
	pipe = init_pipe(shell);
	pipe->last_pipe = 1;
	while (index < shell->parser_tokens_array->size)
	{
		add_element(pipe->commands, parser_tokens[index]);
		add_flags(pipe, parser_tokens[index]);
		index++;
	}
	add_element(shell->pipe_array, pipe);
}

void	add_command(t_shell *shell, int index, int prev)
{
	t_parser_token	**parser_tokens;
	t_pipe			*pipe;

	parser_tokens = (t_parser_token **) shell->parser_tokens_array->array;
	pipe = init_pipe(shell);
	if (prev == 0)
		pipe->first_pipe = 1;
	else
		pipe->middle_pipe = 1;
	while (prev < index)
	{
		add_element(pipe->commands, parser_tokens[prev]);
		add_flags(pipe, parser_tokens[prev]);
		prev++;
	}
	add_element(shell->pipe_array, pipe);
}

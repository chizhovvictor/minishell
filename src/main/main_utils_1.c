/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:00:01 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 12:55:33 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_array_list *tokens)
{
	int	i;

	i = 0;
	while (i < tokens->size)
	{
		free(((t_hashmap *) tokens->array[i])->key);
		free(((t_hashmap *) tokens->array[i])->value);
		free(tokens->array[i]);
		i++;
	}
	free(tokens->array);
	free(tokens);
}

void	clean_array(t_shell *minishell)
{
	free(minishell->input);
	if (has_redir(minishell->parser_tokens_array) \
			&& minishell->cant_execute == 0)
		free_redirects(minishell);
	free_tokenizer_output_array(minishell->tokenizer_array);
	free_parser_tokens(minishell->parser_tokens_array);
	if (minishell->number_of_pipes > 0 && minishell->cant_execute == 0)
	{
		clean_pipe_commands(minishell);
		free_pipe_array(minishell->pipe_array);
		minishell->number_of_pipes = 0;
		minishell->pipe_array->size = 0;
	}
	minishell->lexer_tokens_array->size = 0;
	minishell->parser_tokens_array->size = 0;
	minishell->tokenizer_array->size = 0;
	minishell->cant_execute = 0;
}

void	free_redirects(t_shell *shell)
{
	int				i;
	t_parser_token	**array;
	t_array_list	*tokens;

	i = 0;
	tokens = shell->parser_tokens_array;
	array = (t_parser_token **) tokens->array;
	while (i < tokens->size)
	{
		if (is_redir(array[i]))
		{
			free(array[i]->file);
		}
		i++;
	}
}

void	free_pipe_array(t_array_list *pipe_array)
{
	int		i;
	t_pipe	**pipes;

	i = 0;
	pipes = (t_pipe **) pipe_array->array;
	while (i < pipe_array->size)
	{
		free(pipes[i]->commands->array);
		free(pipes[i]->commands);
		free(pipes[i]);
		i++;
	}
}

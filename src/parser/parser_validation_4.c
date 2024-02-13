/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:54:43 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:54:44 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	validate_tokens(t_array_list *parser_tokens, t_shell *shell)
{
	if (has_only_new_space(parser_tokens))
	{
		handle_cant_execute(shell);
		return ;
	}
	if (ends_with_pipeline(parser_tokens) || ends_with_redir(parser_tokens)
		|| has_consecutive_redirs(parser_tokens)
		|| has_redir_before_pipeline(parser_tokens))
	{
		handle_syntax_error(shell);
		return ;
	}
	if (has_sequence_pipe(parser_tokens))
	{
		handle_syntax_error(shell);
		return ;
	}
}

int	has_sequence_pipe(t_array_list *parser_tokens)
{
	t_parser_token	**array;
	int				i;

	array = (t_parser_token **)parser_tokens->array;
	i = 0;
	while (i < parser_tokens->size - 1)
	{
		if (array[i]->main_type
			== PIPELINE && array[i + 1]->main_type == PIPELINE)
			return (1);
		i++;
	}
	return (0);
}

int	has_only_new_space(t_array_list *parser_tokens)
{
	t_parser_token	**array;

	array = (t_parser_token **)parser_tokens->array;
	return (parser_tokens->size == 1 && array[0]->main_type == NEW_SPACE);
}

int	ends_with_pipeline(t_array_list *parser_tokens)
{
	t_parser_token	**array;

	array = (t_parser_token **)parser_tokens->array;
	return (array[parser_tokens->size - 1]->main_type == PIPELINE);
}

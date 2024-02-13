/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:53:32 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:53:34 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ends_with_redir(t_array_list *parser_tokens)
{
	t_parser_token	**array;

	array = (t_parser_token **)parser_tokens->array;
	return (is_redir(array[parser_tokens->size - 1]));
}

int	has_consecutive_redirs(t_array_list *parser_tokens)
{
	t_parser_token	**array;
	int				i;

	array = (t_parser_token **)parser_tokens->array;
	i = 0;
	while (i < parser_tokens->size - 1)
	{
		if (is_redir(array[i]) && is_redir(array[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

int	has_redir_before_pipeline(t_array_list *parser_tokens)
{
	t_parser_token	**array;
	int				i;

	array = (t_parser_token **)parser_tokens->array;
	i = 0;
	while (i < parser_tokens->size - 1)
	{
		if (is_redir(array[i]) && array[i + 1]->main_type == PIPELINE)
			return (1);
		i++;
	}
	return (0);
}

void	handle_cant_execute(t_shell *shell)
{
	shell->cant_execute = 1;
}

void	handle_syntax_error(t_shell *shell)
{
	shell->cant_execute = 1;
	syntax_error(shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_funcs_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:27:19 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 15:27:20 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tokenize_pipe_and_dollar(char *input, t_shell *shell,
				t_tokenizer_output *po)
{
	if (*input == '|')
		return (add_token(shell, (po
					= tokenize_pipe(input, shell))));
	else if (*input == '$')
		return (add_token(shell, (po
					= tokenize_dollar(input, shell))));
	return (input);
}

char	*tokenize_less_bigger(char *input, t_shell *shell,
				t_tokenizer_output *po)
{
	if (*input == '<')
		return (add_token(shell, (po
					= tokenize_less(input, shell))));
	else if (*input == '>')
		return (add_token(shell, (po
					= tokenize_greater(input, shell))));
	return (input);
}

char	*tokenize_brackets(char *input, t_shell *shell,
				t_tokenizer_output *po)
{
	if (*input == '\'')
		return (add_token(shell, (po
					= tokenize_single_quote(input, shell))));
	else if (*input == '\"')
		return (add_token(shell, (po
					= tokenize_double_quote(input, shell))));
	return (input);
}

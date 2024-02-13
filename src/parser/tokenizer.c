/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:56:17 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:56:19 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize(t_shell *shell)
{
	char				*input;
	int					i;
	t_tokenizer_output	**po_array;

	i = 0;
	input = shell->input;
	po_array = (t_tokenizer_output **) shell->tokenizer_array->array;
	while (*input && shell->cant_execute == 0)
	{
		if (*input == ' ')
			input = add_token(shell, (po_array[i++]
						= tokenize_white_space(input, shell)));
		else if ((*input == '\'') || (*input == '\"'))
			input = tokenize_brackets(input, shell, po_array[i++]);
		else if ((*input == '<') || (*input == '>'))
			input = tokenize_less_bigger(input, shell, po_array[i++]);
		else if ((*input == '|') || (*input == '$'))
			input = tokenize_pipe_and_dollar(input, shell, po_array[i++]);
		else if (ft_isascii(*input) && !is_breaking_character(*input))
			input = add_token(shell, (po_array[i++]
						= tokenize_bare_word(input, shell)));
		else
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:41:17 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:41:18 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_redir(t_array_list *parser_array, t_shell *shell)
{
	t_parser_token	**token_key;
	int				i;

	i = 0;
	token_key = (t_parser_token **) parser_array->array;
	while (i < parser_array->size)
	{
		if (token_key[i]->main_type == REDIRECT_OUTPUT)
			i = redir_out_func(parser_array, i, shell);
		else if (token_key[i]->main_type == REDIRECT_APPEND_OUTPUT)
			i = redir_out_append_func(parser_array, i, shell);
		else if (token_key[i]->main_type == REDIRECT_INPUT)
			i = redir_in_func(parser_array, i, shell);
		else if (token_key[i]->main_type == HEREDOC)
			i = redir_heredoc(parser_array, i, shell);
		else
			i++;
	}
}

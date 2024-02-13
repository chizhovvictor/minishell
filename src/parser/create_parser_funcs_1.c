/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parser_funcs_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:54:14 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 17:54:16 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_joinable(enum e_lexer_type type)
{
	if (type == BARE_WORD || type == SINGLE_QUOTES
		|| type == DOUBLE_QUOTES || type == DOLLAR)
		return (1);
	return (0);
}

void	open_quotes(t_lexer_token **lexer_tokens,
					t_array_list *parser_tokens, int *i, int size)
{
	t_parser_token	*token;

	add_parser_token(parser_tokens, WORDLIST,
		lexer_tokens[*i]->content);
	token = (t_parser_token *) parser_tokens->array[parser_tokens->size - 1];
	*i += 1;
	while (*i < size && is_joinable(lexer_tokens[*i]->type))
	{
		join_words(lexer_tokens[*i], token);
		*i += 1;
	}
}

void	join_words(t_lexer_token *lexer_token, t_parser_token *token)
{
	token->content = ft_strjoin(token->content,
			lexer_token->content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parser_funcs_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:55:02 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/03 13:37:55 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_parser_tokens(t_lexer_token **lexer_tokens,
							t_array_list *parser_tokens, int size)
{
	int	i;

	i = 0;
	if (lexer_tokens[i]->type == WHITE_SPACE)
		i++;
	while (i < size)
	{
		if (is_joinable(lexer_tokens[i]->type))
		{
			open_quotes(lexer_tokens, parser_tokens, &i, size);
			continue ;
		}
		else if (is_lexer_redir(lexer_tokens[i]->type))
			add_redirection(lexer_tokens, parser_tokens, i);
		else if (lexer_tokens[i]->type == PIPE)
			add_parser_token(parser_tokens, PIPELINE, "|");
		i++;
	}
}

int	is_lexer_redir(enum e_lexer_type type)
{
	if (type == LESS_THAN || type == GREATER_THAN
		|| type == LESS_THAN_LESS_THAN || type == GREATER_THAN_GREATER_THAN)
		return (1);
	return (0);
}

void	add_redirection(t_lexer_token **lexer_tokens,
					t_array_list *parser_tokens, int i)
{
	if (lexer_tokens[i]->type == LESS_THAN)
		add_parser_token(parser_tokens, REDIRECT_INPUT, " ");
	else if (lexer_tokens[i]->type == GREATER_THAN)
		add_parser_token(parser_tokens, REDIRECT_OUTPUT, " ");
	else if (lexer_tokens[i]->type == LESS_THAN_LESS_THAN)
		add_parser_token(parser_tokens, HEREDOC, " ");
	else if (lexer_tokens[i]->type == GREATER_THAN_GREATER_THAN)
		add_parser_token(parser_tokens, REDIRECT_APPEND_OUTPUT, " ");
}

void	add_parser_token(t_array_list *tokens_array, \
		enum e_parser_type type, const char *content)
{
	t_parser_token	*token;

	token = malloc(sizeof(t_parser_token));
	token->main_type = type;
	token->sub_type = 0;
	token->flags = 0;
	token->content = ft_strdup(content);
	add_element(tokens_array, token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:19:39 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 18:19:41 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_tokens(t_shell *shell)
{
	int				size;
	t_lexer_token	**lexer_tokens;
	t_array_list	*parser_tokens;

	lexer_tokens = (t_lexer_token **) shell->lexer_tokens_array->array;
	parser_tokens = shell->parser_tokens_array;
	size = shell->lexer_tokens_array->size;
	if (shell->cant_execute
		|| (size == 1 && lexer_tokens[0]->type == WHITE_SPACE))
	{
		shell->cant_execute = 1;
		return ;
	}
	create_parser_tokens(lexer_tokens, parser_tokens, size);
	find_build_in(parser_tokens);
	find_execver(parser_tokens, shell);
	find_dirs(parser_tokens);
	validate_tokens(parser_tokens, shell);
	find_redir(parser_tokens, shell);
}

void	find_redir(t_array_list *parser_tokens, t_shell *shell)
{
	int				i;
	t_parser_token	**array;

	i = 0;
	if (shell->cant_execute)
		return ;
	array = (t_parser_token **)parser_tokens->array;
	while (i < parser_tokens->size)
	{
		if (array[i]->main_type == REDIRECT_OUTPUT)
			handle_redirect(array, i, parser_tokens, shell);
		else if (array[i]->main_type == REDIRECT_APPEND_OUTPUT)
			handle_redirect(array, i, parser_tokens, shell);
		else if (array[i]->main_type == REDIRECT_INPUT)
			handle_redirect(array, i, parser_tokens, shell);
		else if (array[i]->main_type == HEREDOC)
			handle_redirect(array, i, parser_tokens, shell);
		i++;
	}
}

void	handle_redirect(t_parser_token **array, int index,
						t_array_list *parser_tokens, t_shell *shell)
{
	if (redir_error(array, index, shell))
		return ;
	array[index]->file = ft_strdup(array[index + 1]->content);
	delete_parse_element(parser_tokens, index + 1);
}

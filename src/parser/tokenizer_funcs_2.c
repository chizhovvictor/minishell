/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_funcs_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:56:46 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:56:48 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../includes/minishell.h"

t_tokenizer_output	*tokenize_less(char *input, t_shell *shell)
{
	t_tokenizer_output	*po;
	t_lexer_token		*t;

	po = malloc(sizeof(t_tokenizer_output));
	t = malloc(sizeof(t_lexer_token));
	add_element(shell->tokenizer_array, po);
	if (*(input + 1) && *(input + 1) == '<')
	{
		t->type = LESS_THAN_LESS_THAN;
		t->content = ft_strdup("<<");
		po->string = input + 2;
		po->token = *t;
		free(t);
		return (po);
	}
	t->type = LESS_THAN;
	t->content = ft_strdup("<");
	po->string = input + 1;
	po->token = *t;
	free(t);
	return (po);
}

t_tokenizer_output	*tokenize_pipe(char *input, t_shell *shell)
{
	t_tokenizer_output	*po;
	t_lexer_token		*t;

	po = malloc(sizeof(t_tokenizer_output));
	t = malloc(sizeof(t_lexer_token));
	add_element(shell->tokenizer_array, po);
	t->type = PIPE;
	t->content = ft_strdup("|");
	po->string = input + 1;
	po->token = *t;
	free(t);
	return (po);
}

t_tokenizer_output	*tokenize_greater(char *input, t_shell *shell)
{
	t_tokenizer_output	*po;
	t_lexer_token		*t;

	po = malloc(sizeof(t_tokenizer_output));
	t = malloc(sizeof(t_lexer_token));
	add_element(shell->tokenizer_array, po);
	if (*(input + 1) && *(input + 1) == '>')
	{
		t->type = GREATER_THAN_GREATER_THAN;
		t->content = ft_strdup(">>");
		po->string = input + 2;
		po->token = *t;
		free(t);
		return (po);
	}
	t->type = GREATER_THAN;
	t->content = ft_strdup(">");
	po->string = input + 1;
	po->token = *t;
	free(t);
	return (po);
}

t_tokenizer_output	*tokenize_dollar(char *input, t_shell *shell)
{
	t_tokenizer_output	*po;
	t_lexer_token		*t;
	int					i;

	i = 0;
	input++;
	po = malloc(sizeof(t_tokenizer_output));
	t = malloc(sizeof(t_lexer_token));
	add_element(shell->tokenizer_array, po);
	t->content = ft_strdup("");
	if (is_corner_case(input))
	{
		po = dollar_corner_cases(input, t, po);
		return (po);
	}
	i = execute_dollar(input, t, i, shell);
	t->type = DOLLAR;
	po->string = input + i;
	po->token = *t;
	free(t);
	return (po);
}

t_tokenizer_output	*dollar_corner_cases(char *input, t_lexer_token *t,
						t_tokenizer_output *po)
{
	if (*input == '?')
	{
		free(t->content);
		t->content = ft_itoa(g_err_no);
		t->type = DOLLAR;
		po->string = input + 1;
		po->token = *t;
	}
	if (ft_isdigit(*input))
	{
		t->type = DOLLAR;
		po->string = input + 1;
		po->token = *t;
	}
	if (is_breaking_character(*input) || *input == '\0')
	{
		free(t->content);
		t->content = ft_strdup("$");
		t->type = DOLLAR;
		po->string = input;
		po->token = *t;
	}
	free(t);
	return (po);
}

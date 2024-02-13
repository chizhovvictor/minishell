/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:55:23 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 13:15:22 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_readline(t_shell *minishell)
{
	get_line(minishell);
	if (minishell->input == NULL)
		return ;
	add_history(minishell->input);
	check_quotes(minishell);
	tokenize(minishell);
	if (minishell->lexer_tokens_array->size == 0)
	{
		minishell->cant_execute = 1;
		return ;
	}
	parse_tokens(minishell);
}

void	check_quotes(t_shell *shell)
{
	int		i;
	int		single_quote;
	int		double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (shell->input[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
		error("syntax error: unclosed quotes\n", shell, 1);
}

void	get_line(t_shell *minishell)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell->input = readline("$> ");
	if (!minishell->input)
	{
		printf("\033[1A\033[3Cexit\n");
		exit(1);
	}
	else if (*minishell->input == '\0' || !ft_is_ascii(minishell->input))
	{
		free(minishell->input);
		minishell->input = NULL;
		minishell->cant_execute = 1;
	}
}

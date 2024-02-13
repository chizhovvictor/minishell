/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:43:17 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 18:43:19 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_dollar(char *input, t_lexer_token *t, int i, t_shell *shell)
{
	char				*temp;

	while (input[i] && !is_breaking_character(input[i]))
	{
		temp = ft_strndup(input, i + 1);
		if (contain_key(shell->env, temp) && !ft_isalnum(input[i + 1]))
		{
			t->content = ft_strjoin(t->content,
					get_value_by_key(shell->env, (temp)));
			i++;
			free(temp);
			break ;
		}
		free(temp);
		i++;
	}
	return (i);
}

int	open_dollar(char *input, t_shell *shell, t_lexer_token *t)
{
	char	*temp;
	int		i;

	i = 1;
	if (is_corner_case(input + 1))
		return (open_dollar_corner_case(input, t, i));
	while (input[i] && !is_breaking_character(input[i]))
	{
		temp = ft_strndup(input + 1, i);
		if (contain_key(shell->env, temp) && !ft_isalnum(input[i + 1]))
		{
			t->content = ft_strjoin(t->content,
					get_value_by_key(shell->env, (temp)));
			free(temp);
			return (i + 1);
		}
		free(temp);
		i++;
	}
	return (i + 1);
}

int	open_dollar_corner_case(char *input,
							t_lexer_token *t, int i)
{
	char	*temp;

	if (input[i] == '?')
	{
		t->content = ft_strjoin(t->content, (temp = ft_itoa(g_err_no)));
		free(temp);
		t->type = DOLLAR;
		return (i + 1);
	}
	else if (ft_isdigit(input[i]))
	{
		t->type = DOLLAR;
		return (i + 1);
	}
	else if (is_breaking_character(input[i]) || input[i] == '\0')
	{
		t->content = ft_strjoin(t->content, "$");
		t->type = DOLLAR;
		return (i);
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:56:53 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:56:55 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_token(t_shell *shell, struct tokenizer_output *po)
{
	add_element(shell->lexer_tokens_array, &po->token);
	return (po->string);
}

char	*ft_strndup(char *str, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	while (str[i] && i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_breaking_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '>' || c == '<' || c == '|'
		|| c == ';' || c == '$' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_corner_case(char *input)
{
	if (*input == '?')
		return (1);
	if (ft_isdigit(*input))
		return (1);
	if (is_breaking_character(*input) || *input == '\0')
		return (1);
	return (0);
}

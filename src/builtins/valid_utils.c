/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:09:25 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/01 15:32:01 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_token_for_unset(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (1);
		else if (str[i] <= '0' || str[i] >= '{')
			return (1);
		else if (str[i] >= ':' && str[i] <= '@')
			return (1);
		else if (str[i] >= '[' && str[i] <= '^')
			return (1);
		else if (str[i] == '`')
			return (1);
	}
	return (0);
}

int	valid_token_for_ex(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (1);
	if (ft_strchr(str, '='))
	{
		while (str[i] && str[i] != '=')
		{
			if (str[0] >= '0' && str[0] <= '9')
				return (1);
			else if (str[i] <= '0' || str[i] >= '{')
				return (1);
			else if (str[i] >= ':' && str[i] <= '@')
				return (1);
			else if (str[i] >= '[' && str[i] <= '^')
				return (1);
			else if (str[i] == '`')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (valid_token_for_unset(str));
}

int	check_valid_arguments(t_parser_token **token_key, t_shell *shell)
{
	int	check_token;
	int	i;

	i = 0;
	check_token = 0;
	while (++i < shell->parser_tokens_array->size && !check_token)
	{
		if (!ft_strncmp(token_key[0]->content, "unset", 5))
			check_token += valid_token_for_unset(token_key[i]->content);
		else if (!ft_strncmp(token_key[0]->content, "export", 6))
			check_token += valid_token_for_ex(token_key[i]->content);
	}
	if (check_token)
	{
		if (!ft_strncmp(token_key[0]->content, "export", 6))
			ft_putstr_fd("minishell: export: `", 2);
		else if (!ft_strncmp(token_key[0]->content, "unset", 5))
			ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(token_key[i - 1]->content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tmp(char **tmp)
{
	int	i;

	i = 1;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

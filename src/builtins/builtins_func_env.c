/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:26:32 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:30:22 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error1(t_parser_token **token_key)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(token_key[1]->content, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_err_no = 127;
}

void	print_error2(t_parser_token **token_key, int index)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(token_key[index]->content[1], 2);
	write(1, "\n", 1);
	ft_putstr_fd("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n", 2);
	ft_putstr_fd("           [name=value ...] [utility [argument ...]]\n", 2);
	g_err_no = 1;
}

void	print_hash(t_hashmap *hashmap_key)
{
	ft_putstr_fd(hashmap_key->key, 1);
	write(1, "=", 1);
	ft_putstr_fd(hashmap_key->value, 1);
	write(1, "\n", 1);
}

void	env_func(t_hashmap **hashmap_key, t_array_list *line, t_shell *shell)
{
	int				i;
	int				index;
	t_parser_token	**token_key;

	i = 0;
	index = 1;
	g_err_no = 0;
	token_key = (t_parser_token **)line->array;
	if (line->size > 1)
	{
		if (token_key[index]->content[0] != '-')
			print_error1(token_key);
		else
			print_error2(token_key, index);
		return ;
	}
	while (i < shell->env->size)
	{
		if (hashmap_key[i]->value != NULL)
			print_hash(hashmap_key[i]);
		i++;
	}
}

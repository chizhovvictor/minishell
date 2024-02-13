/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:37 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:29:48 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_size(t_array_list *line)
{
	if (line->size <= 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

void	echo_func(t_array_list *line)
{
	int				check_n;
	int				i;
	t_parser_token	**token_key;

	i = 1;
	check_n = 0;
	g_err_no = 0;
	token_key = (t_parser_token **)line->array;
	if (!check_size(line))
		return ;
	if (!(ft_strncmp(token_key[i]->content, "-n", 2)) \
			&& token_key[i]->content[2] == '\0')
	{
		check_n = 1;
		i += 1;
	}
	while (i < line->size)
	{
		ft_putstr_fd(token_key[i]->content, 1);
		if (i + 1 != line->size)
			write(1, " ", 1);
		i++;
	}
	if (!check_n)
		write(1, "\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:40:45 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/07 13:21:20 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_longlong(char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res > LONG_MAX)
			return (1);
	}
	return (0);
}

int	check(char *str)
{
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str == '0')
		str++;
	if (ft_check_longlong(str) || ft_strlen(str) >= 20)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

void	print_error(t_parser_token **token_key, int index)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(token_key[index]->content, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	check_number_arg(t_parser_token **token_key, t_shell *shell)
{
	int	j;

	(void)shell;
	j = 0;
	while (token_key[1]->content[j])
	{
		if (token_key[1]->content[j] == '-' && j == 0)
			j++;
		if (token_key[1]->content[j] == '+' && j == 0)
			j++;
		if (ft_isdigit(token_key[1]->content[j]) == 0)
			return (0);
		j++;
	}
	return (1);
}

void	exit_func(t_array_list *line, t_shell *shell)
{
	t_parser_token	**token_key;

	token_key = (t_parser_token **)line->array;
	g_err_no = 0;
	if (line->size == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (check_number_arg(token_key, shell) && check(token_key[1]->content) == 0)
	{
		if (line->size <= 2)
		{
			ft_putstr_fd("exit\n", 1);
			exit(ft_atoi(token_key[1]->content));
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_err_no = 1;
		}
	}
	else
		print_error(token_key, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:54:51 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:29:08 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_path(t_hashmap **hashmap_key, char *path, t_shell *shell)
{
	char	*pwd;
	char	buf[PATH_MAX];
	int		i;

	i = 0;
	pwd = getcwd(buf, PATH_MAX);
	while (i < shell->env->size)
	{
		if (!ft_strncmp(hashmap_key[i]->key, "OLDPWD", 6))
		{
			free(hashmap_key[i]->value);
			hashmap_key[i]->value = ft_strdup(pwd);
		}
		i++;
	}
	change_path2(hashmap_key, path, shell);
}

char	*find_path(t_hashmap **hashmap_key, t_shell *shell, int task)
{
	int		i;
	char	*path;

	i = 0;
	while (i < shell->env->size)
	{
		if (!ft_strncmp(hashmap_key[i]->key, "PWD", 3) && task == 1)
			path = hashmap_key[i]->value;
		if (!ft_strncmp(hashmap_key[i]->key, "OLDPWD", 6) && task == 2)
			path = hashmap_key[i]->value;
		if (!ft_strncmp(hashmap_key[i]->key, "HOME", 4) && task == 3)
			path = hashmap_key[i]->value;
		i++;
	}
	return (path);
}

void	to_home(t_hashmap **hashmap_key, t_shell *shell)
{
	char	*home_path;

	home_path = ft_strdup(find_path(hashmap_key, shell, 3));
	if (home_path == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_err_no = 1;
	}
	else
		change_path(hashmap_key, home_path, shell);
	free(home_path);
}

void	change_old_path(t_hashmap **hashmap_key, char *path, t_shell *shell)
{
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	change_path(hashmap_key, path, shell);
}

void	cd_func(t_hashmap **hashmap_key, t_array_list *line, t_shell *shell)
{
	int				i;
	t_parser_token	**token_key;

	i = 1;
	g_err_no = 0;
	token_key = (t_parser_token **)line->array;
	if (line->size <= 1 || !ft_strncmp(token_key[i]->content, "~", 2))
	{
		to_home(hashmap_key, shell);
		return ;
	}
	else if (!check_other_cases(hashmap_key, shell, token_key, i))
	{
		g_err_no = 1;
		return ;
	}
}

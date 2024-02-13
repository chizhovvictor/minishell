/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_cd_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:30:02 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/07 13:21:54 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_path2(t_hashmap **hashmap_key, char *path, t_shell *shell)
{
	char	*pwd;
	char	buf[PATH_MAX];
	int		i;

	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_err_no = 1;
	}
	pwd = getcwd(buf, PATH_MAX);
	i = 0;
	while (i < shell->env->size)
	{
		if (!ft_strncmp(hashmap_key[i]->key, "PWD", 3))
		{
			free(hashmap_key[i]->value);
			hashmap_key[i]->value = ft_strdup(pwd);
		}
		i++;
	}
}

int	check_null(char *path)
{
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		free(path);
		return (0);
	}
	return (1);
}

int	check_other_cases(t_hashmap **hashmap_key, t_shell *shell, \
		t_parser_token **token_key, int i)
{
	char	*path;

	if (!ft_strncmp(token_key[i]->content, "-", 2))
	{
		if (find_path(hashmap_key, shell, 2) == NULL)
		{
			check_null(NULL);
			return (0);
		}
		path = ft_strdup(find_path(hashmap_key, shell, 2));
		change_old_path(hashmap_key, path, shell);
	}
	else
	{
		if (ft_strchr(token_key[i]->content, '~'))
		{
			path = ft_strdup(find_path(hashmap_key, shell, 3));
			path = ft_strjoin(path, ft_strchr(token_key[i]->content, '/'));
		}
		else
			path = ft_strdup(token_key[i]->content);
		change_path(hashmap_key, path, shell);
	}
	free(path);
	return (1);
}

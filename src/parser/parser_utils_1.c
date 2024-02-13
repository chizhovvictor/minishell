/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:53:12 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:53:13 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_array_size(char **string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*ft_str_to_lower(char *content)
{
	char	*str;
	int		i;

	str = ft_strdup(content);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	free_array(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

int	is_directory(char *path)
{
	struct stat	struct_stat;

	if (access(path, F_OK | R_OK | X_OK) == 0)
	{
		if (stat(path, &struct_stat) != 0)
		{
			return (0);
		}
		return (S_ISDIR(struct_stat.st_mode));
	}
	return (0);
}

void	add_execver_from_path(t_parser_token **parser_tokens,
							char **paths, int *i, int *j)
{
	char		*path;
	struct stat	s;

	path = ft_strjoin(ft_strjoin(ft_strdup(paths[*j]), "/"),
			parser_tokens[*i]->content);
	if (access(path, X_OK) == 0
		&& parser_tokens[*i]->main_type == WORDLIST)
	{
		stat(path, &s);
		if (S_ISREG(s.st_mode))
		{
			free(path);
			parser_tokens[*i]->main_type = EXECUTABLE_PATH;
			return ;
		}
	}
	free(path);
}

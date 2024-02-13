/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_finding_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:48:46 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:48:48 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_execver(t_array_list *parser_tokens_array, t_shell *shell)
{
	t_parser_token	**parser_tokens;

	parser_tokens = (t_parser_token **)(parser_tokens_array->array);
	parse_execver_from_path(parser_tokens, shell);
	add_execvere(parser_tokens, shell);
}

void	add_execvere(t_parser_token **parser_tokens, t_shell *shell)
{
	int			size;
	int			i;
	struct stat	s;

	i = 0;
	size = shell->parser_tokens_array->size;
	while (i < size)
	{
		if (parser_tokens[i]->main_type == WORDLIST)
		{
			if (access(parser_tokens[i]->content, X_OK) == 0
				&& parser_tokens[i]->main_type == WORDLIST)
			{
				stat(parser_tokens[i]->content, &s);
				if (S_ISREG(s.st_mode))
				{
					parser_tokens[i]->main_type = EXECUTABLE;
				}
			}
		}
		i++;
	}
}

void	parse_execver_from_path(t_parser_token **parser_tokens, t_shell *shell)
{
	char	**paths;
	char	*temp;
	int		i;
	int		j;
	int		size_sub;

	if (!has_path(shell))
		return ;
	temp = ft_strdup(get_value_by_key(shell->env, "PATH"));
	paths = ft_split(temp, ':');
	size_sub = get_array_size(paths);
	i = 0;
	while (i < shell->parser_tokens_array->size)
	{
		j = 0;
		while (j < size_sub)
		{
			add_execver_from_path(parser_tokens, paths, &i, &j);
			j++;
		}
		i++;
	}
	free(temp);
	free_array(paths);
}

void	find_dirs(t_array_list *parser_tokens)
{
	int				i;
	t_parser_token	**tokens;

	tokens = (t_parser_token **) parser_tokens->array;
	i = 0;
	while (i < parser_tokens->size)
	{
		if (tokens[i]->main_type == WORDLIST)
			if (is_directory(tokens[i]->content))
				tokens[i]->main_type = DIRECTORY;
		i++;
	}
}

void	find_build_in(t_array_list *parser_tokens)
{
	int				i;
	t_parser_token	**tokens;

	tokens = (t_parser_token **) parser_tokens->array;
	i = 0;
	while (i < parser_tokens->size)
	{
		if (tokens[i]->main_type == WORDLIST)
		{
			add_echo(tokens[i], parser_tokens, i);
			add_cd(tokens[i]);
			add_pwd(tokens[i]);
			add_exprt(tokens[i]);
			add_unset(tokens[i]);
			add_envp(tokens[i]);
			add_exit(tokens[i]);
		}
		i++;
	}
}

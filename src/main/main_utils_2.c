/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:00:09 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/03 11:00:13 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_pipe_commands(t_shell *shell)
{
	int			i;
	t_pipe		**pipes;

	i = 0;
	pipes = (t_pipe **) shell->pipe_array->array;
	while (i < shell->pipe_array->size)
	{
		pipes[i]->commands->size = 0;
		i++;
	}
}

void	free_parser_tokens(t_array_list *tokens)
{
	int				i;
	t_parser_token	*po;
	t_parser_token	**array;

	i = 0;
	array = (t_parser_token **) tokens->array;
	while (i < tokens->size)
	{
		po = array[i];
		free(po->content);
		free(po);
		i++;
	}
}

void	free_tokenizer_output_array(t_array_list *tokens)
{
	int					i;
	t_tokenizer_output	*po;
	t_tokenizer_output	**array;

	i = 0;
	array = (t_tokenizer_output **) tokens->array;
	while (i < tokens->size)
	{
		po = array[i];
		free(po->token.content);
		free(po);
		i++;
	}
}

int	ft_is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}

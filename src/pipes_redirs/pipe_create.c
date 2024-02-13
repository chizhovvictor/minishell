/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:40:20 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:40:22 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe_list(t_shell *shell)
{
	int				index;
	int				prev_index;
	int				last_pipe;
	t_parser_token	**parser_tokens;

	if (shell->cant_execute || too_many_pipes(shell))
		return ;
	init_number_of_pipes(&index, &prev_index, &last_pipe);
	parser_tokens = (t_parser_token **) shell->parser_tokens_array->array;
	while (index < shell->parser_tokens_array->size)
	{
		if (parser_tokens[index]->main_type == PIPELINE)
		{
			last_pipe = index;
			last_pipe++;
			add_command(shell, index, prev_index);
			index++;
			prev_index = index;
			continue ;
		}
		index++;
	}
	add_last_command(shell, last_pipe);
}

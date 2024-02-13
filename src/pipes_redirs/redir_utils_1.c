/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:41:34 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:41:35 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redir(t_array_list *tokens)
{
	int	i;

	i = 0;
	while (i < tokens->size)
	{
		if (is_redir(((t_parser_token **) tokens->array)[i]))
			return (1);
		i++;
	}
	return (0);
}

void	close_pipes(int i, int fd_array[1000][2])
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(fd_array[j][0]);
		close(fd_array[j][1]);
		j++;
	}
}

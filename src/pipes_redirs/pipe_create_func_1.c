/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create_func_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:40:28 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/01 19:40:32 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_number_of_pipes(int *index, int *prev_index, int *last_pipe)
{
	*index = 0;
	*last_pipe = 0;
	*prev_index = 0;
}

int	too_many_pipes(t_shell *shell)
{
	if (shell->number_of_pipes > 250)
	{
		shell->cant_execute = 1;
		printf("fork: Resource temporarily unavailable\n");
		g_err_no = 1;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:51:17 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 12:53:11 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_STRUCTS_H
# define PIPE_STRUCTS_H

# include "minishell.h"

typedef struct s_pipe
{
	t_array_list	*commands;
	int				first_pipe;
	int				middle_pipe;
	int				last_pipe;
	int				is_execve;
	int				is_builtin;
	int				is_redir;
	int				pid;
	t_shell			*shell;
}					t_pipe;

#endif

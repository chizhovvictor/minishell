/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_funcs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:23:24 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:23:26 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_FUNCS_H
# define PIPE_FUNCS_H

# include "minishell.h"
# include "pipe_structs.h"

void	count_pipes(t_shell *shell);
void	add_command(t_shell *shell, int index, int prev);
void	add_last_command(t_shell *shell, int index);
int		has_pipes(t_shell *shell);
void	create_pipe_list(t_shell *shell);
void	execute_pipes(t_shell *shell);
void	execute_command_in_pipe(t_pipe *pipe);
void	add_flags(t_pipe *pipe, t_parser_token *token);
int		is_redir(t_parser_token *token);
void	execute_pipe(t_pipe *pipe_token,
			int i, int fd_array[1000][2], int size);
t_pipe	*init_pipe(t_shell *shell);
void	clean_pipe_commands(t_shell *shell);
int		too_many_pipes(t_shell *shell);
void	init_number_of_pipes(int *index, int *prev_index, int *last_pipe);
void	close_pipes(int i, int fd_array[1000][2]);

#endif

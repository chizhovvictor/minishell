/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:24:47 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:24:48 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_FUNC_H
# define REDIRECT_FUNC_H

# include "minishell.h"

int		redir_out_func(t_array_list *parser_tokens, int i, t_shell *shell);
int		redir_out_append_func(t_array_list *parser_tokens,
			int i, t_shell *shell);
int		redir_in_func(t_array_list *parser_tokens, int i, t_shell *shell);
int		redir_heredoc(t_array_list *parser_tokens, int i, t_shell *shell);
void	find_redir(t_array_list *parser_tokens, t_shell *shell);
int		redir_error(t_parser_token **parser_tokens, int i, t_shell *shell);
void	delete_parse_element(t_array_list *parser_tokens, int i);
void	execute_heredoc(int i, char *delimiter);
void	free_redirects(t_shell *shell);
void	find_last_err(t_shell *shell);
int		heredoc_in_pipe(t_array_list *parser_array, t_shell *shell);
void	do_pipe_redirects(t_pipe *pipe_token, int fd_array[1000][2],
			int i, int heredocced);

#endif

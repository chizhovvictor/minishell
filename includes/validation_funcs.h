/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_funcs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:25:47 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:26:59 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_FUNCS_H
# define VALIDATION_FUNCS_H

# include "minishell.h"

int		has_only_new_space(t_array_list *parser_tokens);
int		ends_with_pipeline(t_array_list *parser_tokens);
int		ends_with_redir(t_array_list *parser_tokens);
int		has_consecutive_redirs(t_array_list *parser_tokens);
int		has_redir_before_pipeline(t_array_list *parser_tokens);
void	handle_cant_execute(t_shell *shell);
void	handle_syntax_error(t_shell *shell);
void	remove_parse_element(t_array_list *parser_tokens, int index);
void	handle_redirect(t_parser_token **array, int index, \
		t_array_list *parser_tokens, t_shell *shell);
void	print_2d_arr(char **pString);
int		has_sequence_pipe(t_array_list *parser_tokens);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:03:21 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:05:40 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"
# include "array_list.h"

typedef struct s_minishell
{
	t_array_list	*env;
	char			**envp;
	t_array_list	*lexer_tokens_array;
	t_array_list	*parser_tokens_array;
	t_array_list	*tokenizer_array;
	t_array_list	*pipe_array;
	int				number_of_pipes;
	int				only_redir;
	int				cant_execute;
	char			*input;
}					t_shell;

#endif

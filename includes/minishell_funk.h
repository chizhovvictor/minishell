/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funk.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:45:29 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:03:07 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNK_H
# define MINISHELL_FUNK_H

# include "minishell.h"
# include "array_list.h"
# include "parser_structs.h"

typedef struct s_hashmap	t_hashmap;
typedef struct s_arrayList	t_array_list;
typedef struct s_minishell	t_shell;

t_shell			*create_shell(void);
void			welcome_message(void);
void			print_env(char **envp);
t_array_list	*add_env(char **envp);
void			add_tokens(t_shell *minishell);
void			clean_array(t_shell *minishell);
void			print_all_args(t_array_list *list);
void			free_tokenizer_output_array(t_array_list *tokens);
int				ft_is_ascii(char *str);
void			free_parser_tokens(t_array_list *tokens);
void			execute_builtin(t_array_list *token_array, \
		t_shell *shell, int i);
int				has_redir(t_array_list *tokens);
void			execute_redir(t_array_list *tokens, t_shell *shell);
void			clean_all(t_shell *shell);
void			free_env(t_array_list *tokens);
int				command_func3(t_parser_token **token_key, t_array_list \
		*parser_tokens, t_shell *shell, char **envp);
void			command_func2(t_parser_token **token_key, t_array_list \
		*parser_tokens, t_shell *shell, char **envp);
void			command_func(t_shell *shell, char **envp);
void			execute_builtin(t_array_list *token_array, \
		t_shell *shell, int i);
void			ex_func(t_array_list *line, t_shell *shell, char **envp);
t_hashmap		*init_hashmap(void);
void			free_pipe_array(t_array_list *pipe_array);
void			execute_hashmap(char **array, t_hashmap *hashmap);

#endif

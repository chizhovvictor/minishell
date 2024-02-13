/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:15:40 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:22:38 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_STRUCTS_H
# define PARSER_STRUCTS_H

# include "minishell.h"

enum e_lexer_type {
	WHITE_SPACE,
	LESS_THAN_LESS_THAN,
	LESS_THAN,
	DOLLAR,
	PIPE,
	GREATER_THAN,
	GREATER_THAN_GREATER_THAN,
	BARE_WORD,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
};

enum e_parser_type {
	NEW_SPACE,
	WORDLIST,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND_OUTPUT,
	HEREDOC,
	PIPELINE,
	BIlD_IN,
	CD,
	PWD,
	ECHO,
	EXPORT,
	ENVP,
	UNSET,
	EXIT,
	EXECUTABLE,
	EXECUTABLE_PATH,
	DIRECTORY,
};

typedef struct parser {
	enum e_parser_type	main_type;
	enum e_parser_type	sub_type;
	int					flags;
	char				*content;
	char				*file;
	char				*heredoc;
}						t_parser_token;

typedef struct token {
	enum e_lexer_type	type;
	char				*content;
}						t_lexer_token;

typedef struct tokenizer_output {
	char			*string;
	struct token	token;
}					t_tokenizer_output;

#endif

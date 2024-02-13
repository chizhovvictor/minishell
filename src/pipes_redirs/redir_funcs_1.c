/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_funcs_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:41:25 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 15:27:59 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out_append_func(t_array_list *parser_tokens, int i, t_shell *shell)
{
	int				fd;
	t_parser_token	**token_key;

	if (parser_tokens->size == 1)
		shell->only_redir = 1;
	token_key = (t_parser_token **) parser_tokens->array;
	fd = open(token_key[i]->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(token_key[i]->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	delete_parse_element(parser_tokens, i);
	return (i);
}

int	redir_out_func(t_array_list *parser_tokens,
				int i, t_shell *shell)
{
	int				fd;
	t_parser_token	**token_key;

	if (parser_tokens->size == 1)
		shell->only_redir = 1;
	token_key = (t_parser_token **) parser_tokens->array;
	fd = open(token_key[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(token_key[i]->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	delete_parse_element(parser_tokens, i);
	return (i);
}

int	redir_in_func(t_array_list *parser_tokens, int i, t_shell *shell)
{
	int				fd;
	t_parser_token	**token_key;

	if (parser_tokens->size == 1)
		shell->only_redir = 1;
	token_key = (t_parser_token **) parser_tokens->array;
	fd = open(token_key[i]->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(token_key[i]->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	delete_parse_element(parser_tokens, i);
	return (i);
}

int	redir_heredoc(t_array_list *parser_tokens, int i, t_shell *shell)
{
	int				fd;
	t_parser_token	**token_key;

	token_key = (t_parser_token **) parser_tokens->array;
	token_key[i]->heredoc = "here_doc";
	if (parser_tokens->size == 1)
		shell->only_redir = 1;
	fd = open(token_key[i]->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error(": No such file or directory\n", shell, 2);
		exit(1);
	}
	execute_heredoc(fd, token_key[i]->file);
	close(fd);
	fd = open(token_key[i]->heredoc, O_RDONLY);
	if (fd < 0)
	{
		error(": No such file or directory\n", shell, 2);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	delete_parse_element(parser_tokens, i);
	return (i);
}

void	execute_heredoc(int i, char *delimiter)
{
	char			*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (ft_strcmp(input, delimiter) == 0)
			break ;
		write(i, input, ft_strlen(input));
		write(i, "\n", 1);
		free(input);
	}
}

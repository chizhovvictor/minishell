/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:54:37 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 19:54:38 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_exit(t_parser_token *token)
{
	char	*temp;

	temp = ft_str_to_lower(token->content);
	if (ft_strcmp(temp, "exit") == 0)
	{
		token->main_type = BIlD_IN;
		token->sub_type = EXIT;
	}
	free(temp);
}

void	add_envp(t_parser_token *token)
{
	char	*temp;

	temp = ft_str_to_lower(token->content);
	if (ft_strcmp(temp, "env") == 0)
	{
		token->main_type = BIlD_IN;
		token->sub_type = ENVP;
	}
	free(temp);
}

void	add_unset(t_parser_token *token)
{
	char	*temp;

	temp = ft_str_to_lower(token->content);
	if (ft_strcmp(temp, "unset") == 0)
	{
		token->main_type = BIlD_IN;
		token->sub_type = UNSET;
	}
	free(temp);
}

void	add_exprt(t_parser_token *token)
{
	char	*temp;

	temp = ft_str_to_lower(token->content);
	if (ft_strcmp(temp, "export") == 0)
	{
		token->main_type = BIlD_IN;
		token->sub_type = EXPORT;
	}
	free(temp);
}

void	add_pwd(t_parser_token *token)
{
	char	*temp;

	temp = ft_str_to_lower(token->content);
	if (ft_strcmp(temp, "pwd") == 0)
	{
		token->main_type = BIlD_IN;
		token->sub_type = PWD;
	}
	free(temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:46:39 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 13:32:02 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_func(void)
{
	char	*pwd;
	char	buf[PATH_MAX];

	g_err_no = 0;
	pwd = getcwd(buf, PATH_MAX);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:59:43 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 12:55:04 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_structs.h"

t_array_list	*add_env(char **envp)
{
	int				i;
	t_array_list	*env;
	t_hashmap		*hashmap;

	i = 0;
	env = create_array_list();
	while (envp[i])
	{
		hashmap = create_hashmap(envp[i]);
		add_element(env, hashmap);
		i++;
	}
	return (env);
}

t_hashmap	*create_hashmap(char *string)
{
	t_hashmap	*hashmap;
	char		**array;

	hashmap = init_hashmap();
	array = ft_split(string, '=');
	hashmap->key = ft_strdup(array[0]);
	if (get_array_size(array) < 2)
	{
		free_array(array);
		hashmap->value = NULL;
		return (hashmap);
	}
	if (get_array_size(array) > 2)
		execute_hashmap(array, hashmap);
	else if (ft_strncmp(array[0], "OLDPWD", 6) == 0)
		hashmap->value = NULL;
	else
		hashmap->value = ft_strdup(array[1]);
	free_array(array);
	return (hashmap);
}

void	execute_hashmap(char **array, t_hashmap *hashmap)
{
	int			i;

	hashmap->value = ft_strdup(array[1]);
	i = 2;
	while (array[i])
	{
		hashmap->value = ft_strjoin(hashmap->value, "=");
		hashmap->value = ft_strjoin(hashmap->value, array[i]);
		i++;
	}
}

t_hashmap	*init_hashmap(void )
{
	t_hashmap	*hashmap;

	hashmap = malloc(sizeof(t_hashmap));
	hashmap->key = NULL;
	hashmap->value = NULL;
	return (hashmap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:37:17 by vbudilov          #+#    #+#             */
/*   Updated: 2023/07/04 12:56:27 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value_by_key(t_array_list *list, char *key)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		if (ft_strcmp(((t_hashmap *) list->array[i])->key, key) == 0)
			return (((t_hashmap *) list->array[i])->value);
		i++;
	}
	return (NULL);
}

int	contain_key(t_array_list *list, char *key)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		if (ft_strcmp(((t_hashmap *) list->array[i])->key, key) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	change_value_by_key(t_array_list *list, char *key, char *value)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		if (ft_strcmp(((t_hashmap *) list->array[i])->key, key) == 0)
		{
			free(((t_hashmap *) list->array[i])->value);
			((t_hashmap *) list->array[i])->value = ft_strdup(value);
			return ;
		}
		i++;
	}
}

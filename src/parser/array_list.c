/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:35:42 by vbudilov          #+#    #+#             */
/*   Updated: 2023/06/29 16:35:45 by vbudilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_structs.h"

t_array_list	*create_array_list(void )
{
	t_array_list	*list;

	list = (t_array_list *) malloc(sizeof(t_array_list));
	list->size = 0;
	list->capacity = 1000;
	list->array = (void **) malloc(list->capacity * sizeof(void *));
	return (list);
}

void	add_element(t_array_list *list, void *element)
{
	if (list->size == list->capacity)
	{
		list->capacity *= 2;
		list->array = ft_realloc(list->array, list->capacity * sizeof(void *));
	}
	list->array[list->size] = element;
	list->size++;
}

void	delete_element(t_array_list *list, int index)
{
	if (index >= list->size)
	{
		return ;
	}
	while (index < list->size - 1)
	{
		list->array[index] = list->array[index + 1];
		index++;
	}
	list->size--;
}

void	free_array_list(t_array_list *list)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		free(list->array[i]);
		i++;
	}
	free(list->array);
	free(list);
}

void	delete_parse_element(t_array_list *parser_tokens, int i)
{
	t_parser_token	**array;

	array = (t_parser_token **) parser_tokens->array;
	if (is_redir(array[i]))
		free(array[i]->file);
	else
		free(array[i]->content);
	free(array[i]);
	delete_element(parser_tokens, i);
}

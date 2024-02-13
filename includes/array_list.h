/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:28:54 by vchizhov          #+#    #+#             */
/*   Updated: 2023/07/03 12:55:49 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LIST_H
# define ARRAY_LIST_H

# include "minishell_structs.h"
# include "minishell_funk.h"

typedef struct s_hashmap
{
	char	*key;
	char	*value;
}			t_hashmap;

typedef struct s_arrayList
{
	void	**array;
	int		size;
	int		capacity;
}			t_array_list;

t_array_list	*create_array_list(void);
void			add_element(t_array_list *list, void *element);
void			delete_element(t_array_list *list, int index);
void			free_array_list(t_array_list *list);

char			*get_value_by_key(t_array_list *list, char *key);
void			print_all_tokens(t_array_list *list);
void			*find_element_by_index(t_array_list *list, int index);
int				contain_key(t_array_list *list, char *key);
void			change_value_by_key(t_array_list *list, char *key, char *value);
void			add_element_by_index(t_array_list *list, \
		void *element, int index);

int				ft_strcmp(const char *s1, const char *s2);
t_hashmap		*create_hashmap(char *string);
void			*ft_realloc(void *ptr, size_t size);

#endif

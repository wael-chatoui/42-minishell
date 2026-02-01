/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:33:37 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sets the value of an environment variable
** @param env: Pointer to the environment list head
** @param name: The name of the variable
** @param value: The value to set
*/
void	set_env_val(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

/*
** Removes an environment variable
** @param env: Pointer to the environment list head
** @param name: The name of the variable to remove
*/
void	remove_env_var(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

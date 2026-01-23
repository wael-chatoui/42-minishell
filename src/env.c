/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:05:00 by wael              #+#    #+#             */
/*   Updated: 2026/01/23 12:07:18 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

static t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	int		j;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	node->name = ft_substr(env_str, 0, j);
	if (env_str[j] == '=')
		node->value = ft_strdup(env_str + j + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (!head)
		{
			head = new_env_node(envp[i]);
			current = head;
		}
		else
		{
			current->next = new_env_node(envp[i]);
			current = current->next;
		}
		i++;
	}
	return (head);
}

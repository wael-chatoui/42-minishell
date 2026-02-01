/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:58:10 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*create_env_str(t_env *node)
{
	char	*joined;
	char	*res;

	if (node->value)
	{
		joined = ft_strjoin(node->name, "=");
		res = ft_strjoin(joined, node->value);
		free(joined);
		return (res);
	}
	return (ft_strdup(node->name));
}

/*
** Converts the environment list to an array
** @param env: The environment list
** @return: Methods array of environment strings
*/
char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;
	t_env	*tmp;

	arr = malloc(sizeof(char *) * (count_env_vars(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = create_env_str(tmp);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Gets the value of an environment variable
** @param env: The environment list
** @param name: The name of the variable
** @return: The value of the variable
*/
char	*get_env_val(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

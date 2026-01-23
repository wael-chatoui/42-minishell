/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/23 13:30:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			write(1, env->name, ft_strlen(env->name));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	char	*name;
	char	*value;
	char	*eq;
	int		i;

	if (!args[1])
		return (ft_env(*env));
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			name = ft_substr(args[i], 0, eq - args[i]);
			value = eq + 1; // Assuming value is valid pointer
			set_env_val(env, name, value);
			free(name);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (args[i])
	{
		tmp = *env;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, args[i]))
			{
				if (prev)
					prev->next = tmp->next;
				else
					*env = tmp->next;
				free(tmp->name);
				if (tmp->value)
					free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **args)
{
    (void)args;
	exit(0);
	return (0);
}

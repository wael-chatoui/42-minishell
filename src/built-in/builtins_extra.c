/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:33:45 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Executes the env command (prints environment variables)
** @param env: Environment list
** @return: 0 on success
*/
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

/*
** Executes the export command (add/update env variable)
** @param args: Arguments array
** @param env: Environment list
** @return: 0 on success
*/
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
			value = eq + 1;
			set_env_val(env, name, value);
			free(name);
		}
		i++;
	}
	return (0);
}

/*
** Executes the unset command (remove env variable)
** @param args: Arguments array
** @param env: Environment list
** @return: 0 on success
*/
int	ft_unset(char **args, t_env **env)
{
	int		i;

	i = 1;
	while (args[i])
	{
		remove_env_var(env, args[i]);
		i++;
	}
	return (0);
}

/*
** Executes the exit command
** @param args: Arguments array
** @return: Does not return (exits process) or 0
*/
int	ft_exit(char **args)
{
	(void)args;
	exit(0);
	return (0);
}

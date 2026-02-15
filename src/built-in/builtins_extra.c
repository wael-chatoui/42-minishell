/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/15 17:10:31 by wael             ###   ########.fr       */
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

static int	export_one(char *arg, t_env **env)
{
	char	*eq;
	char	*name;
	int		ret;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!is_valid_id(arg))
			return (print_id_error(arg));
		return (0);
	}
	name = ft_substr(arg, 0, eq - arg);
	ret = 0;
	if (!is_valid_id(name))
		ret = print_id_error(arg);
	else
		set_env_val(env, name, eq + 1);
	return (free(name), ret);
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	int		ret;

	if (!args[1])
		return (print_export(*env));
	ret = 0;
	i = 0;
	while (args[++i])
	{
		if (export_one(args[i], env))
			ret = 1;
	}
	return (ret);
}

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

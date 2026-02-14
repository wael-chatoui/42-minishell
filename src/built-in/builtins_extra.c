/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
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
	char	*eq;
	int		i;
	int		ret;

	if (!args[1])
		return (print_export(*env));
	ret = 0;
	i = 0;
	while (args[++i])
	{
		eq = ft_strchr(args[i], '=');
		if (!eq)
			continue ;
		name = ft_substr(args[i], 0, eq - args[i]);
		if (!is_valid_id(name))
			ret = print_id_error(args[i]);
		else
			set_env_val(env, name, eq + 1);
		free(name);
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

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	write(2, "exit\n", 5);
	if (!args[1])
		return (-1);
	if (!is_numeric(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		g_sig = 255;
		return (-1);
	}
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	g_sig = ft_atoi(args[1]) % 256;
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**env_names_array(t_env *env, int size)
{
	char	**names;
	int		i;

	names = malloc(sizeof(char *) * (size + 1));
	if (!names)
		return (NULL);
	i = 0;
	while (env)
	{
		names[i++] = env->name;
		env = env->next;
	}
	names[i] = NULL;
	return (names);
}

static void	sort_names(char **names, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(names[j], names[j + 1]) > 0)
			{
				tmp = names[j];
				names[j] = names[j + 1];
				names[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_one_export(char *name, t_env *env)
{
	char	*val;

	write(1, "declare -x ", 11);
	write(1, name, ft_strlen(name));
	val = get_env_val(env, name);
	if (val)
	{
		write(1, "=\"", 2);
		write(1, val, ft_strlen(val));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

int	print_export(t_env *env)
{
	char	**names;
	int		size;
	int		i;

	size = env_list_size(env);
	names = env_names_array(env, size);
	if (!names)
		return (1);
	sort_names(names, size);
	i = 0;
	while (names[i])
	{
		print_one_export(names[i], env);
		i++;
	}
	free(names);
	return (0);
}

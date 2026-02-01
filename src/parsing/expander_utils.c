/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:30:08 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Extracts variable name from string
** @param str: String starting after $
** @return: The variable name
*/
char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

/*
** Gets value of a variable from env or global status
** @param name: Variable name
** @param env: Environment list
** @return: Allocated string value
*/
char	*get_val(char *name, t_env *env)
{
	char	*val;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(g_sig));
	val = get_env_val(env, name);
	if (val)
		return (ft_strdup(val));
	return (NULL);
}

/*
** Joins two strings and frees the first one
** @param s1: First string (freed)
** @param s2: Second string (not freed)
** @return: New joined string
*/
char	*join_and_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

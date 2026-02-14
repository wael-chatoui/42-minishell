/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*join_and_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	*append_char(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (join_and_free(s, buf));
}

char	*append_substr(char *s, char *str, int start, int len)
{
	char	*sub;
	char	*res;

	sub = ft_substr(str, start, len);
	res = join_and_free(s, sub);
	free(sub);
	return (res);
}

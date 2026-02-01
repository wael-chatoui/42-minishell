/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:50:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:30:14 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar(char **res, char *str, int *i, t_env *env)
{
	char	*var;
	char	*val;

	var = get_var_name(&str[*i + 1]);
	if (var && *var)
	{
		val = get_val(var, env);
		if (val)
		{
			*res = join_and_free(*res, val);
			free(val);
		}
		*i += ft_strlen(var) + 1;
		free(var);
	}
	else
	{
		if (var)
			free(var);
		(*i)++;
	}
}

/*
** Expands variables in a string
** @param str: Input string
** @param env: Environment list
** @return: Expanded string
*/
char	*expand_str(char *str, t_env *env)
{
	char	*res;
	char	*tmp;
	int		i;
	int		start;

	res = ft_strdup("");
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, start, i - start);
			res = join_and_free(res, tmp);
			free(tmp);
			handle_dollar(&res, str, &i, env);
			start = i;
		}
		else
			i++;
	}
	tmp = ft_substr(str, start, i - start);
	res = join_and_free(res, tmp);
	free(tmp);
	return (res);
}

/*
** Expands token value, handling quotes
** @param str: Token value string
** @param env: Environment list
** @return: Expanded string
*/
char	*expand_token_value(char *str, t_env *env)
{
	char	*res;
	char	*inner;

	if (!str)
		return (NULL);
	if (str[0] == '\'')
		res = ft_substr(str, 1, ft_strlen(str) - 2);
	else if (str[0] == '"')
	{
		inner = ft_substr(str, 1, ft_strlen(str) - 2);
		res = expand_str(inner, env);
		free(inner);
	}
	else
		res = expand_str(str, env);
	return (res);
}

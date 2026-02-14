/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:50:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
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
		*res = append_char(*res, '$');
		if (var)
			free(var);
		(*i)++;
	}
}

static void	handle_squote(char **res, char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (*i > start)
	{
		*res = append_substr(*res, str, start, *i - start);
	}
	if (str[*i] == '\'')
		(*i)++;
}

static void	handle_dquote(char **res, char *str, int *i, t_env *env)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			handle_dollar(res, str, i, env);
		else
		{
			*res = append_char(*res, str[*i]);
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
}

char	*expand_token_value(char *str, t_env *env)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_squote(&res, str, &i);
		else if (str[i] == '"')
			handle_dquote(&res, str, &i, env);
		else if (str[i] == '$')
			handle_dollar(&res, str, &i, env);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

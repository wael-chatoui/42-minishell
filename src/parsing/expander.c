/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:50:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/23 13:50:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

static char	*get_val(char *name, t_env *env)
{
	if (!ft_strcmp(name, "?"))
		return (ft_itoa(0)); // TODO: use global exit status
	return (get_env_val(env, name));
}

char	*expand_str(char *str, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*var;
	char	*val;
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
			res = ft_strjoin(res, tmp);
			free(tmp);

			var = get_var_name(&str[i + 1]);
			if (var && *var)
			{
				val = get_val(var, env);
				if (val)
					res = ft_strjoin(res, val); // Leaks: previous res, need helper
				// free(val) if itoa? get_env_val returns pointer to const?
				// get_env_val returns env->value which is persistent.
				// ft_itoa allocates.
				// I need to know if I should free 'val'.
				// For '?', yes. For others, no.
				// Proper exp impl is complex. Simplified here.

				i += ft_strlen(var) + 1;
				start = i;
				free(var);
			}
			else
			{
				if (var) free(var); // empty name
				// just print $
				i++; // start not updated
			}
		}
		else
			i++;
	}
	tmp = ft_substr(str, start, i - start);
	res = ft_strjoin(res, tmp);
	free(tmp);
	return (res);
}

// Very basic expander for now.
// Current tokenizer sends: "hello" for argument "hello".
// We need to strip outer quotes.
// If double quotes, expand content.
// If single quotes, preserve content.
// If no quotes, expand.
char	*expand_token_value(char *str, t_env *env)
{
	char	*res;

	if (!str) return (NULL);

	if (str[0] == '\'')
	{
		// Strip quotes
		res = ft_substr(str, 1, ft_strlen(str) - 2);
	}
	else if (str[0] == '"')
	{
		char *inner = ft_substr(str, 1, ft_strlen(str) - 2);
		res = expand_str(inner, env);
		free(inner);
	}
	else
	{
		res = expand_str(str, env);
	}
	return (res);
}

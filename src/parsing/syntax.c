/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/23 13:08:35 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_type(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

static int	check_pipe_errors(t_token *tokens)
{
	t_token	*tmp;

	if (tokens->type == PIPE)
	{
		write(2, "minishell: syntax error near `|'\n", 33);
		return (1);
	}
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && (!tmp->next || tmp->next->type == PIPE))
		{
			write(2, "minishell: syntax error near `|'\n", 33);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_redir_errors(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (is_redir_type(tmp->type))
		{
			if (!tmp->next || tmp->next->type != WORD)
			{
				write(2, "minishell: syntax error near `", 30);
				if (tmp->next)
					write(2, tmp->next->value, ft_strlen(tmp->next->value));
				else
					write(2, "newline", 7);
				write(2, "'\n", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
	{
		write(2, "minishell: syntax error: unclosed quote\n", 40);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (check_pipe_errors(tokens))
		return (1);
	if (check_redir_errors(tokens))
		return (1);
	return (0);
}

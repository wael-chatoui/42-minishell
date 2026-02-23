/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/23 13:22:51 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_word(char *input, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (input[*i])
	{
		if (quote)
		{
			if (input[*i] == quote)
				quote = 0;
		}
		else
		{
			if (input[*i] == '\'' || input[*i] == '"')
				quote = input[*i];
			else if (is_space(input[*i]) || is_operator(input[*i]))
				break ;
		}
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

static void	handle_pipe_or_redir(char *input, int *i, char **val, int *type)
{
	if (input[*i] == '|')
	{
		*val = ft_strdup("|");
		*type = PIPE;
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*val = ft_strdup("<<");
			*type = HEREDOC;
			*i += 2;
		}
		else
		{
			*val = ft_strdup("<");
			*type = REDIR_IN;
			(*i)++;
		}
	}
}

static int	handle_token(char *input, int *i, char **val, int *type)
{
	if (input[*i] == '|' || input[*i] == '<')
	{
		handle_pipe_or_redir(input, i, val, type);
		return (1);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*val = ft_strdup(">>");
			*type = APPEND;
			*i += 2;
		}
		else
		{
			*val = ft_strdup(">");
			*type = REDIR_OUT;
			(*i)++;
		}
		return (1);
	}
	return (0);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		index;
	char	*val;
	int		type;

	head = NULL;
	i = 0;
	index = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (!handle_token(input, &i, &val, &type))
		{
			val = handle_word(input, &i);
			type = WORD;
		}
		token_add_back(&head, new_token(val, type, index++));
	}
	return (head);
}

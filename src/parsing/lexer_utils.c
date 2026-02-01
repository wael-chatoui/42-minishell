/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:27:47 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if the character is a delimiter (space, tab, newline)
** @param c: The character to check
** @return: 1 if it is a delimiter, 0 otherwise
*/
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
** Checks if the character is a special operator (|, <, >)
** @param c: The character to check
** @return: 1 if it is an operator, 0 otherwise
*/
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Creates a new token node
** @param value: The string value of the token
** @param type: The type of the token
** @param index: The position index of the token
** @return: A pointer to the new token
*/
t_token	*new_token(char *value, int type, int index)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->index = index;
	token->input = NULL;
	token->env_list = NULL;
	token->next = NULL;
	return (token);
}

/*
** Adds a token to the end of the list
** @param head: Pointer to the head of the list
** @param new: The new token to add
*/
void	token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

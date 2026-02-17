/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:55:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:30:23 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< Updated upstream
/*
** Fills the command arguments array
** @param cmd: The command structure
** @param tokens: Pointer to the list of tokens
** @param env: The environment structure
*/
static int	has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

=======
>>>>>>> Stashed changes
static void	fill_args_loop(t_cmd *cmd, t_token **curr, int *i, t_env *env)
{
	char	*expanded;

	if ((*curr)->type == WORD || (*curr)->type == ARG || (*curr)->type == CMD)
	{
		expanded = expand_token_value((*curr)->value, env);
		if (expanded[0] || has_quotes((*curr)->value))
			cmd->args[(*i)++] = expanded;
		else
			free(expanded);
	}
	else if ((*curr)->type == REDIR_IN || (*curr)->type == REDIR_OUT
		|| (*curr)->type == APPEND || (*curr)->type == HEREDOC)
	{
		add_redir(cmd, *curr, (*curr)->next);
		if ((*curr)->next)
			*curr = (*curr)->next;
	}
}

static void	fill_args(t_cmd *cmd, t_token **tokens, t_env *env)
{
	int		arg_count;
	int		i;
	t_token	*curr;

	arg_count = count_args(*tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	i = 0;
	curr = *tokens;
	while (curr && curr->type != PIPE)
	{
		fill_args_loop(cmd, &curr, &i, env);
		curr = curr->next;
	}
	cmd->args[i] = NULL;
	*tokens = curr;
}

t_cmd	*parse_tokens(t_token *tokens, t_env *env)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new_cmd;

	head = NULL;
	curr = NULL;
	while (tokens)
	{
		new_cmd = create_cmd();
		if (!new_cmd)
			return (NULL);
		if (!head)
			head = new_cmd;
		else
			curr->next = new_cmd;
		curr = new_cmd;
		curr->head = head;
		curr->env = env;
		fill_args(curr, &tokens, env);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}

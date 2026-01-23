/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:55:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/23 12:55:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->token = NULL;
	cmd->env = NULL;
	cmd->next = NULL;
	cmd->head = NULL;
	return (cmd);
}

static void	add_redir(t_cmd *cmd, t_token *token, t_token *file_token)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = token->type;
	new_redir->file = NULL;
	if (file_token)
		new_redir->file = ft_strdup(file_token->value);
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		last = cmd->redir;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == ARG || tmp->type == CMD)
			count++;
		else if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
			tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (count);
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
		if (curr->type == WORD || curr->type == ARG || curr->type == CMD)
		{
			cmd->args[i++] = expand_token_value(curr->value, env);
		}
		else if (curr->type == REDIR_IN || curr->type == REDIR_OUT || \
			curr->type == APPEND || curr->type == HEREDOC)
		{
			add_redir(cmd, curr, curr->next);
			if (curr->next)
				curr = curr->next;
		}
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
		curr->env = env; // Store env in cmd if needed
		fill_args(curr, &tokens, env);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}

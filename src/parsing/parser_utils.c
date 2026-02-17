/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:30:21 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
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

static void	redir_add_back(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*last;

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

static void	init_hd_redir(t_redir *redir, char *value)
{
	int	len;

	len = ft_strlen(value);
	if (len >= 2 && (value[0] == '\'' || value[0] == '"')
		&& value[len - 1] == value[0])
	{
		redir->heredoc_expand = 0;
		redir->file = ft_substr(value, 1, len - 2);
	}
	else
	{
		redir->heredoc_expand = 1;
		redir->file = ft_strdup(value);
	}
}

void	add_redir(t_cmd *cmd, t_token *token, t_token *file_token)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = token->type;
	new_redir->file = NULL;
	new_redir->heredoc_expand = 0;
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	if (file_token && token->type == HEREDOC)
		init_hd_redir(new_redir, file_token->value);
	else if (file_token)
		new_redir->file = expand_token_value(file_token->value, cmd->env);
	redir_add_back(cmd, new_redir);
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == ARG || tmp->type == CMD)
			count++;
		else if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (count);
}

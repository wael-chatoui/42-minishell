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

/*
** Creates a new command node and initializes its values
** @return: A pointer to the new command
*/
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

/*
** Adds a redirection to the command's redirection list
** @param cmd: The command structure
** @param token: The redirection token
** @param file_token: The token containing the filename or delimiter
*/
void	add_redir(t_cmd *cmd, t_token *token, t_token *file_token)
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

/*
** Count arguments in tokens
*/
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/02/23 13:02:55 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig;

static int	run_cmds(t_token *tokens, t_env **env)
{
	t_cmd	*cmds;
	int		ret;

	ret = 0;
	cmds = parse_tokens(tokens, *env);
	if (cmds)
	{
		if (!collect_heredocs(cmds))
			ret = execute_cmds(cmds, env);
		free_cmds(cmds);
	}
	return (ret);
}

static int	process_input(char *input, t_env **env)
{
	t_token	*tokens;
	int		ret;

	add_history(input);
	if (check_unclosed_quotes(input))
	{
		g_sig = 258;
		return (0);
	}
	tokens = lexer(input);
	if (!tokens)
		return (0);
	if (check_syntax(tokens))
	{
		g_sig = 258;
		free_tokens(tokens);
		return (0);
	}
	ret = run_cmds(tokens, env);
	free_tokens(tokens);
	return (ret);
}

void	miniloop(t_env **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input[0] != '\0')
		{
			if (process_input(input, env))
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	setup_parent_signals();
	miniloop(&env);
	rl_clear_history();
	free_env(env);
	return (g_sig);
}

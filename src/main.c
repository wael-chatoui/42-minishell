/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:57:59 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig;


** Main loop of the shell
** @param env: Pointer to the environment list
*/
static void	process_input(char *input, t_env **env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	cmds = parse_tokens(tokens, *env);
	if (cmds)
	{
		execute_cmds(cmds, env);
		free_cmds(cmds);
	}
	free_tokens(tokens);
}

/*
** Main loop of the shell
** @param env: Pointer to the environment list
*/
void	miniloop(t_env **env)
{
	char	*input;

	while (true)
	{
		input = readline("minishell > ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input[0] != '\0')
			process_input(input, env);
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
	free_env(env);
	return (0);
}

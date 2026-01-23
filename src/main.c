/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/01/23 13:51:54 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig;

void	logger(char *type, t_token *token)
{
	if (!ft_strcmp(type, "DEBUG"))
	{
		while (token)
		{
			printf("[%s]\n", type);
			printf("value: %s\n", token->value);
			printf("index: %d\n", token->index);
			printf("type: %d\n\n", token->type);
			token = token->next;
		}
	}
	if (!ft_strcmp(type, "ENV"))
	{
		env = data;
		while (env && ft_strcmp(env->name, "PATH"))
			env = env->next;
		if (env)
		printf("%s=%s\n", env->name, env->value);
	}
}

void	tokenize(t_token *token, char *input)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	start = 0;
	index = 0;

	// Reset token fields
	token->next = NULL;
	token->value = NULL;
	token->input = ft_strdup(input); // This causes leaks if looped effectively without cleaning

	t_token *curr = token; // Use curr to traverse

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\n' || input[i + 1] == '\0')
		{
			if (i - start + (input[i + 1] == '\0' && input[i] != ' ') > 0)
			{
				curr->value = ft_substr(input, start, i - start + \
					(input[i + 1] == '\0' && input[i] != ' '));
				curr->index = index;
				curr->type = WORD;
				if (curr->value[0] == '|')
					curr->type = PIPE;

				if (input[i + 1] != '\0')
				{
					curr->next = malloc(sizeof(t_token));
					curr = curr->next;
					curr->next = NULL;
					curr->value = NULL; // init
					curr->input = NULL; // init
				}
				index++;
			}
			start = i + 1;
		}
		i++;
	}
	// printf("\n");
}

void	miniloop(t_token *token, t_env **env)
{
	char	*input;
	t_cmd	*cmds;

	while (true)
	{
		input = readline("minishell > ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokenize(token, input);
		// logger("DEBUG", token);

		cmds = parse_tokens(token, *env);
		execute_cmds(cmds, env);
		free_cmds(cmds);

		// Clean up tokens
        // token points to stack variable, but its ->next chain is malloced
        // free_tokens(token) frees the chain.
        // But src/token.c implementation iterates starting from 'token'.
        // If 'token' is stack, free(token) is invalid.
        // Wait, src/token.c:
        // while (token) { tmp=token; token=token->next; ... free(tmp); }
        // If I pass address of stack variable, it tries to free stack. CRASH.

        // My implementation in previous main.c:
        // tmp = token->next; while(tmp) ... free(tmp);

        // I should use my logic for stack token cleanup OR change how I use token.
        // Since I want to use src/token.c, I can't pass the stack variable directly if it frees it.
        // I will manually free the chain skipping the first node, to avoid recreating free_tokens here.

        // Actually, better: token.next is the head of the malloced chain? No.
        // My tokenize uses 'token' as the first node.

        // I will manually clean up here to be safe and simple, ignoring src/token.c for the stack node.
        if (token->input) { free(token->input); token->input = NULL; }
        if (token->value) { free(token->value); token->value = NULL; }
        if (token->next)
        {
            free_tokens(token->next);
            token->next = NULL;
        }

		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	token;
	t_env	*env;

	(void)ac;
	(void)av;

	env = init_env(envp);
	print_signature();

	// Init token safely
	token.next = NULL;
	token.value = NULL;
	token.input = NULL;

	miniloop(&token, &env);
	free_env(env);
	return (0);
}

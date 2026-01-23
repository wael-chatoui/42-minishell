/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/01/23 13:49:10 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logger(char *type, void *data)
{
	t_token	*token;
	t_env	*env;

	if (!ft_strcmp(type, "DEBUG"))
	{
		token = data;
		while (token)
		{
			printf("[DEBUG]\n");
			printf("value: %s\n", token->value);
			printf("index: %d\n", token->index);
			printf("type: %d\n", token->type);
			printf("------------------------------\n\n");
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

void	tokenize(t_token **token_head, char *input)
{
	int		i;
	int		start;
	int		index;
	t_token	*current;
	t_token	*new_node;

	i = 0;
	start = 0;
	index = 0;
	*token_head = NULL;
	current = NULL;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\n' || input[i + 1] == '\0')
		{
			if (i - start + (input[i + 1] == '\0' && input[i] != ' ') > 0)
			{
				new_node = malloc(sizeof(t_token));
				ft_bzero(new_node, sizeof(t_token));
				new_node->input = NULL;
				new_node->value = ft_substr(input, start, i - start + \
					(input[i + 1] == '\0' && input[i] != ' '));
				new_node->index = index;
				new_node->type = WORD;
				if (new_node->value[0] == '|' && (new_node->value[1] == \
					'\0' || new_node->value[1] == ' '))
					new_node->type = PIPE;
				
				if (current)
				{
					current->next = new_node;
					current = new_node;
				}
				else
				{
					*token_head = new_node;
					current = new_node;
					current->input = ft_strdup(input);
				}
				index++;
			}
			start = i + 1;
		}
		i++;
	}
	printf("\n");
}

void	miniloop(t_env *env)
{
	char	*input;
	t_token	*token;

	(void)env;
	while (true)
	{
		input = readline("minishell > ");
		if (!input)
			break ;
		tokenize(&token, input);
		logger("DEBUG", token);
		logger("ENV", env);
		free_tokens(token);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env(envp);
	print_signature();
	miniloop(env);
	free_env(env);
	return (EXIT_FAILURE);
}

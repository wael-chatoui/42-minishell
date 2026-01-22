/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/01/22 21:08:12 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logger(char *type, t_token *token)
{
	if (!ft_strcmp(type, "DEBUG"))
	{
		while (token->next)
		{
			printf("[%s]\n", type);
			printf("value: %s\n", token->value);
			printf("index: %d\n", token->index);
			printf("type: %d\n\n", token->type);
			token = token->next;
		}
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
	token->input = ft_strdup(input);
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\n' || input[i + 1] == '\0')
		{
			if (i - start + (input[i + 1] == '\0' && input[i] != ' ') > 0)
			{
				token->value = ft_substr(input, start, i - start + \
					(input[i + 1] == '\0' && input[i] != ' '));
				token->index = index;
				token->type = WORD;
				if (token->value[0] == '|')
					token->type = PIPE;
				if (input[i + 1] != '\0')
				{
					token->next = malloc(sizeof(t_token));
					token = token->next;
					token->next = NULL;
				}
				token = token->next;
				token->next = NULL;
				index++;
			}
			start = i + 1;
		}
		i++;
	}
	printf("\n");
}

void	miniloop(t_token *token)
{
	char	*input;

	while (true)
	{
		input = readline("minishell > ");
		tokenize(token, input);
		logger("DEBUG", token);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	token;

	(void)ac;
	(void)av;
	(void)envp;
	print_signature();
	miniloop(&token);
	return (EXIT_FAILURE);
}

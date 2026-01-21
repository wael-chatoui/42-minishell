/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:27:53 by wael              #+#    #+#             */
/*   Updated: 2026/01/20 20:57:31 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signature()
{
	ft_putstr("\n"
		"╔════════════════════════════════════════════════════════════════════════════╗\n"
		"║" GREEN "    ███╗   ███╗██╗███╗   ██╗██╗      ██████╗  █████╗ ███████╗               " RESET "║\n"
		"║" GREEN "    ████╗ ████║██║████╗  ██║██║      ██╔══██╗██╔══██╗██╔════╝               " RESET "║\n"
		"║" GREEN "    ██╔████╔██║██║██╔██╗ ██║██║█████╗██████╔╝███████║█████╗                 " RESET "║\n"
		"║" GREEN "    ██║╚██╔╝██║██║██║╚██╗██║██║╚════╝██╔═══╝ ██╔══██║██╔══╝                 " RESET "║\n"
		"║" GREEN "    ██║ ╚═╝ ██║██║██║ ╚████║██║      ██║     ██║  ██║██║                    " RESET "║\n"
		"║" GREEN "    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝      ╚═╝     ╚═╝  ╚═╝╚═╝                    " RESET "║\n"
		"╠════════════════════════════════════════════════════════════════════════════╣\n"
		"║" GREEN "                    Welcome to Mini-paf v1.0                                " RESET "║\n"
		"║" GREEN "                        by Wael & Samir                                     " RESET "║\n"
		"╚════════════════════════════════════════════════════════════════════════════╝\n"
		RESET "\n");
}

void	tokenize(t_token *token, char *input)
{
	int	i;

	i = 0;
	token->input = ft_strdup(input);
	while (input[i])
	{
		
		i++;
	}
	(void)input;
}

void	miniloop(t_token *token)
{
	char	*input;

	while (true)
	{
		input = readline("minishell > ");
		tokenize(token, input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_token	token;

	print_signature();
	miniloop(&token);
	return (EXIT_FAILURE);
}

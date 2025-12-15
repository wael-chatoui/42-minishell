/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:36:34 by wael              #+#    #+#             */
/*   Updated: 2025/12/12 17:05:56 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	len_to_newline(t_gnl_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}

static char	*get_line(t_gnl_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	lstcpy_str(list, next_str);
	return (next_str);
}

static void	lstadd_front(t_gnl_list **list, char *buf)
{
	t_gnl_list	*new_node;
	t_gnl_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
	{
		free(buf);
		return ;
	}
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

static void	create_list(t_gnl_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		lstadd_front(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		if (list)
			dealloc(&list, NULL, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}

// #include <stdio.h>

// int	main()
// {
// 	int fd = open("empty.txt", O_RDONLY);
// 	char *gnl = get_next_line(fd);
// 	printf("%s", gnl);
// 	free(gnl);
// 	return (0);
// }

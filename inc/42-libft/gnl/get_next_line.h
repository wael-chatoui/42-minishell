/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:09:56 by wael              #+#    #+#             */
/*   Updated: 2026/01/22 17:46:10 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_gnl_list
{
	char				*str_buf;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd);
void		lstcpy_str(t_gnl_list *list, char *str);
t_gnl_list	*find_last_node(t_gnl_list *list);
int			found_newline(t_gnl_list *list);
void		polish_list(t_gnl_list **list);
void		dealloc(t_gnl_list **list, t_gnl_list *clean_node, char *buf);
#endif

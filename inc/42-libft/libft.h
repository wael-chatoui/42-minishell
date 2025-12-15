/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:12:33 by wchatoui          #+#    #+#             */
/*   Updated: 2025/12/05 15:08:45 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t	ft_abs(int n);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_atoi_base(char *str, char *base);
char	*ft_itoa(int n);
char	**ft_split(const char *str, char charset);
int		ft_count_words(const char *str, const char c);
//
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);
bool	ft_isspace(int c);
bool	ft_islower(char c);
bool	ft_is_in(char const c, char const *str);
//
void	ft_putchar(char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
bool	ft_islower(char c);
bool	ft_isupper(int c);
//
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
//
char	*ft_strdup(char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
//
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *memBlock, int c, size_t size);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t elCount, size_t elSize);
//
void	ft_free_split(char **res, int j);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
// bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:49:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/10 11:52:20 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD
#  define FD 1024
# endif

# define MAX_INT 2147483647
# define MIN_INT -2147483648

// colors
# define RESET		"\001\033[0m\002"
# define BLACK		"\001\033[0;30m\002"
# define RED		"\001\033[0;31m\002"
# define GREEN		"\001\033[0;32m\002"
# define YELLOW		"\001\033[0;33m\002"
# define BLUE		"\001\033[0;34m\002"
# define PURPLE		"\001\033[0;35m\002"
# define CYAN		"\001\033[0;36m\002"
# define WHITE		"\001\033[0;37m\002"
# define GRAY		"\001\033[90m\002"
# define ORANGE		"\001\033[38;5;208m\002"

// Background
# define B_BLACK	"\033[40m"
# define B_RED		"\033[41m"
# define B_GREEN	"\033[42m"
# define B_YELLOW	"\033[43m"
# define B_BLUE		"\033[44m"
# define B_PURPLE	"\033[45m"
# define B_CYAN		"\033[46m"
# define B_WHITE	"\033[47m"

# define FREE1 0b0001
# define FREE2 0b0010

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_front(t_list **lst, t_list *new_lst);
int		ft_lstadd_back(t_list **lst, t_list *new_lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_arrchr(char **arr, char *to_find);

int		is_whitespace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strscmp(const char *s1, const char *s2, char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_atos(char **arr, char separator);
int		overflow_check(const char *s, void (*f)(int, void *), void *param);
int		ft_lstsize(t_list *lst);
int		ft_putaddr(long int nbr, char *base, int fd);
int		ft_printf(const char *s, ...);
int		ft_dprintf(const int fd, const char *s, ...);

int		ft_abs(int n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

int		ft_putnbr_fd(int n, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_hex(unsigned long int nbr, char *base, int fd);

size_t	ft_strlen(const char *s);
size_t	ft_strclen(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);

char	*ft_strchr(const char *s, int c);
int		ft_strchr_i(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrstr(const char *big, const char *little);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, char c);
char	*ft_strdup_except_char(char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2, const int flags);
char	*ft_charjoin(char *s1, char const c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_free(char *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*get_next_line(int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
void	ft_sort_normalized(char **arr);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_lstchr_n(t_list *lst, int n);
t_list	*ft_lstchr(t_list *lst, void *content);
void	ft_lstprint(const char *msg, t_list *lst);

// debug.c
void	debug_color(const char *msg, const char *color);
void	warning(const char *msg);
void	error(const char *msg);
void	alert(const char *msg);
int		malloc_assert(void *mem, const char *file, int line,
			const char *function);

char	*ft_pad(char *s, char c);
size_t	ft_occ(char *s, char c);

#endif

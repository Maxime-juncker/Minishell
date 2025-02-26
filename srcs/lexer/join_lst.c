/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:38 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/22 11:15:30 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_we_join_a_space(char *str_ref, int len, char content)
{
	return ((str_ref && !is_symbol((str_ref)[len - 1])
		&& (str_ref)[len - 1] != ' ' && is_symbol(content))
				|| (str_ref && is_symbol((str_ref)[len - 1])
				&& content != ' ' && !is_symbol(content)));
}

static int	skip_spaces( char content_c, char *str_ref, char quote, int len )
{
	if (content_c == ' ' && !str_ref)
	{
		return (1);
	}
	if (!quote && content_c == ' ' && str_ref \
		&& len > 0 && str_ref[len - 1] == ' ')
	{
		return (1);
	}
	return (0);
}

static void	join_loop(char *content, char **str_ref, int *len)
{
	int		i;
	char	quote;

	if (ignore_prompt(content))
		return ;
	quote = 0;
	i = -1;
	while (content[++i])
	{
		quote = toggle_quote(content[i], quote);
		while (skip_spaces(content[i], *str_ref, quote, *len))
			i++;
		if (should_we_join_a_space(*str_ref, *len, content[i]))
		{
			*str_ref = ft_charjoin(*str_ref, ' ');
			if (*str_ref == NULL)
				return ;
			(*len)++;
			continue ;
		}
		*str_ref = ft_charjoin(*str_ref, content[i]);
		if (*str_ref == NULL)
			return ;
		(*len)++;
	}
}

char	*join_lst(t_list *lst)
{
	char	*str;
	int		len;

	str = NULL;
	len = 0;
	while (lst)
	{
		join_loop(lst->content, &str, &len);
		if (str == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (str);
}

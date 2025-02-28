/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:48 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/28 12:17:47 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	toggle_quote(char c, char quote)
{
	if (c == '\'' || c == '\"')
	{
		if (quote == 0)
			return (c);
		else if (quote == c)
			return (0);
	}
	return (quote);
}

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

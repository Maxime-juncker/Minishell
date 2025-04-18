/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:34 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/02 12:15:02 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_occ_reverse(const char *str, int i)
{
	int	occ;
	int	c;

	occ = 0;
	c = str[i];
	while (i >= 0 && str[i] == c)
	{
		occ++;
		i--;
		while (i >= 0 && str[i] == ' ')
			i--;
	}
	return (occ);
}

int	check_token_error(const char *cmd_line, int i, int max_occ, char to_find)
{
	int	occ;

	occ = count_occ_reverse(cmd_line, i);
	if (occ > max_occ)
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token `",
			RED);
		occ = 0;
		while (cmd_line[i] == to_find && occ < max_occ)
		{
			ft_dprintf(2, "%c", to_find);
			i++;
			occ++;
		}
		ft_dprintf(2, "\'\n\033[0m");
		return (SYNTAX_ERR);
	}
	return (0);
}

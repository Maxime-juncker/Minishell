/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:44 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:45 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	return (i);
}

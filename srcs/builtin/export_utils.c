/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:59:03 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/11 15:53:31 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(char **argv)
{
	int		i;
	int		diff;
	char	*temp;
	int		size;

	diff = 1;
	size = arrlen((void **)argv);
	while (diff)
	{
		i = 0;
		diff = 0;
		while (i < (size - 1))
		{
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				diff = 1;
			}
			i++;
		}
	}
}

static char	**update_env(char *arg, char **env, int append)
{
	char	**cpy;
	int		i;

	cpy = malloc((arrlen((void **)env) + 2 - append) * sizeof(char *));
	if (malloc_assert(cpy, __FILE__, __LINE__, __FUNCTION__))
		return (env);
	i = -1;
	while (env && env[++i])
	{
		if (append && !ft_strscmp(env[i], arg, "+="))
			cpy[i] = ft_strjoin_free(env[i], ft_strchr(arg, '=')
					+ (ft_strchr(env[i], '=') != NULL), FREE1);
		else
			cpy[i] = env[i];
		if (malloc_assert(cpy[i], __FILE__, __LINE__, __FUNCTION__))
			return (free(cpy), env);
	}
	if (!append)
	{
		cpy[i] = ft_strdup(arg);
		if (malloc_assert(cpy[i++], __FILE__, __LINE__, __FUNCTION__))
			return (free(cpy), env);
	}
	free(env);
	return (cpy[i] = NULL, cpy);
}

int	export_env(t_command_table *table, char *arg, int append)
{
	if (ft_strchr(arg, '='))
		table->env = update_env(arg, table->env, append);
	table->exp = update_env(arg, table->exp, append);
	if (!table->env || !table->exp)
		return (MALLOC_ERR);
	return (0);
}

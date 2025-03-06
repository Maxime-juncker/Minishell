/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:06:14 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 11:11:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_prompt(t_command_table *table, char *line)
{
	t_list	*lst;
	int		res;

	lst = NULL;
	if (check_cmd_line(process_line(line, table->env, &table->code), &table->code) != 0)
		return (0);
	res = handle_process_cmd(table, line, &table->code, &lst);
	ft_lstclear(&lst, cleanup_pacakge);
	return (res);
}

int	load_config(t_command_table *table)
{
	int		fd;
	char	*path;
	char	*line;

	path = find_env_var(table->env, "HOME", NULL);
	if (path == NULL)
		return (0);
	path = ft_strjoin_free(path, "/.minishellrc", FREE1);
	if (malloc_assert(path, __FILE__, __LINE__, __FUNCTION__))
		return (0);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (0);
	table->setup_fd = fd;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		exec_prompt(table, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (table->code);
}
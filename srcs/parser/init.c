/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:25:59 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/20 13:10:05 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	count_args(char *cmd_str)
{
	int	n_args;
	int	i;
	int	quote;

	quote = 0;
	n_args = 1;
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
			quote = toggle_quote(quote, cmd_str[i]);
		if (!quote && cmd_str[i] == ' ' && cmd_str[i + 1])
			n_args++;
		i++;
	}
	return (n_args + 1);
}

static int	create_arg(char **cmd_arg, char *str)
{
	char	*arg;
	int		i;
	int		quote;
	int		start;

	i = 0;
	quote = 0;
	start = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = toggle_quote(str[i], quote);
		else if (quote == 0 && str[i] == ' ')
			break ;
		i++;
	}
	arg = malloc(sizeof(char) * (i - start + 1));
	if (malloc_assert(arg, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (*cmd_arg = NULL, MALLOC_ERR);
	ft_strlcpy(arg, &str[start], i - start + 1);
	*cmd_arg = arg;
	return (0);
}

static int	get_args(t_command *cmd, char *cmd_str)
{
	int	i;
	int	quote;
	int	n_args;

	cmd->args = malloc(sizeof(char *) * (count_args(cmd_str) + 1));
	if (malloc_assert(cmd->args, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	i = 0;
	quote = 0;
	n_args = 0;
	while (cmd_str[i])
	{
		while (cmd_str[i] == ' ')
			i++;
		if (cmd_str[i] == '\0')
			break ;
		if (create_arg(&cmd->args[n_args], &cmd_str[i]) == MALLOC_ERR)
			return (MALLOC_ERR);
		while (cmd_str[i] && (quote || cmd_str[i] != ' '))
			if (cmd_str[i++] == '\'' || cmd_str[i - 1] == '\"')
				quote = toggle_quote(cmd_str[i - 1], quote);
		n_args++;
	}
	cmd->args[n_args] = NULL;
	return (0);
}

static int	init_cmd(t_command_table *table, t_command *cmd, char *cmd_str)
{
	int	i;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (get_args(cmd, cmd_str) == MALLOC_ERR)
		return (MALLOC_ERR);
	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == '<' && cmd->args[i][1] == '<'
			&& heredoc(table, cmd, cmd->args[i + 1]) != 0)
			return (MALLOC_ERR);
	}
	return (0);
}

int	init_table(char *line, t_command_table *table)
{
	char	**commands;
	size_t	i;

	commands = ft_split_pipe(line);
	table->n_commands = 0;
	if (malloc_assert(commands, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (malloc_assert(table->commands, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (cleanup_arr((void **)commands), MALLOC_ERR);
	i = -1;
	while (++i < table->n_commands)
		if (init_cmd(table, &table->commands[i], commands[i]) == MALLOC_ERR)
			return (cleanup_arr((void **)commands), table->n_commands = i + 1,
				close_all_fds(table), cleanup_table(table), MALLOC_ERR);
	if (init_redir(table) == MALLOC_ERR)
		return (cleanup_arr((void **)commands), MALLOC_ERR);
	return (cleanup_arr((void **)commands), 0);
}

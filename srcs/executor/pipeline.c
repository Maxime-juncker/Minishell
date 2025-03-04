/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:50 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/04 13:33:14 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>

int	g_signal_received = 0;

static int	seek_cmd(t_command_table *table, char *name)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < table->n_commands)
	{
		tmp = get_exec_name(table->commands[i].args[0]);
		if (ft_strcmp(tmp, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	wait_for_process(t_command_table *table, int *childs, int *code)
{
	int		pid;
	size_t	i;

	i = -1;
	while (childs[++i])
	{
		pid = wait(code);
		if (WIFEXITED(*code))
			*code = WEXITSTATUS(*code);
		else 
			*code += 128;
		if (pid == -1)
		{
			if (g_signal_received)
			{
				while (i < table->n_commands)
					kill(childs[i++], g_signal_received);
				if (seek_cmd(table, table->name) == -1)
				{
					if (g_signal_received == SIGQUIT)
						printf("Quit (core dumped)");
					printf("\n");
				}
			}
			return (close_all_fds(table), *code);
		}
	}
	return (close_all_fds(table), *code);
}

static int	setup_pipeline(int **childs, t_command_table *table)
{
	g_signal_received = 0;
	signal(SIGQUIT, handle_signal);
	*childs = ft_calloc(table->n_commands + 2, sizeof(int));
	if (malloc_assert(childs, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	(*childs)[table->n_commands] = -1;
	return (0);
}

int	run_stage(t_command_table *table, int i, int *childs, t_list *args)
{
	int	code;

	code = check_path(table->commands[i].args[0], table->env);
	if (code != 0)
	{
		close_fds(table->commands[i]);
		childs[i] = -1;
		return (code);
	}
	if (env_stage(table, table->commands[i], &code,
			(t_free_pkg){childs, args}))
	{
		return (code);
	}
	childs[i] = run_command(&table->commands[i], table,
			(t_free_pkg){childs, args});
	return (code);
}

int	run_pipeline(t_command_table *table, t_list *args)
{
	size_t	i;
	int		code;
	int		*childs;

	if (table->commands[0].n_args == 0)
		return (close_all_fds(table), 0);
	if (setup_pipeline(&childs, table) == MALLOC_ERR)
		return (MALLOC_ERR);
	i = 0;
	show_table(*table);
	while (i < table->n_commands)
	{
		if (table->commands[i].n_args != 0)
		{
			code = run_stage(table, i, childs, args);
		}
		i++;
	}
	return (code = wait_for_process(table, childs, &code), free(childs), code);
}

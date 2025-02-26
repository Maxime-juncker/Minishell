/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:50 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/23 00:17:04 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	ignore_prompt(char *prompt)
{
	while (*prompt)
	{
		if (!(*prompt == ' ' || (*prompt >= 9 && *prompt <= 13))
			&& in_base(*prompt, ":!") == -1)
			return (0);
		prompt++;
	}
	return (1);
}

static char	*get_folder(void)
{
	char	*temp;
	char	buffer[1024];
	char	*folder;

	if (!getcwd(buffer, sizeof(buffer)))
		return (ft_strdup(""));
	folder = ft_strdup(buffer);
	if (!folder)
		return (NULL);
	temp = folder;
	if (folder[1] != '\0')
	{
		while (*folder && ft_strchr(folder, '/') != 0)
		{
			folder++;
		}
	}
	folder = ft_strjoin(folder, ":");
	free(temp);
	return (folder);
}

static char	*new_prompt_txt(char **env)
{
	char	*txt;
	char	*folder;

	folder = get_folder();
	if (!folder)
		return (NULL);
	txt = ft_strjoin(BLUE, NULL);
	if (!txt)
		return (free(folder), NULL);
	txt = ft_strjoin_free(txt, folder, FREE1 | FREE2);
	if (!txt)
		return (NULL);
	txt = ft_charjoin(txt, ' ');
	if (!txt)
		return (NULL);
	txt = ft_strjoin_free(txt, GREEN, FREE1);
	if (!txt)
		return (NULL);
	txt = ft_strjoin_free(txt, find_env_var(env, "USER", NULL), FREE1);
	if (!txt)
		return (NULL);
	txt = ft_strjoin_free(txt, "$\033[0m ", FREE1);
	return (txt);
}

static int	handle_process_cmd(t_command_table *table, char *line,
	char *process_cmd, int *code)
{
	if (ignore_prompt(line))
	{
		free(process_cmd);
		free(line);
		return (0);
	}
	else if (ft_strcmp(line, "\n"))
		add_history(line);
	if (ft_strcmp(line, "\n") && ft_strcmp(line, "!") && ft_strcmp(line, ":"))
	{
		free(line);
		if (!process_cmd)
			return (MALLOC_ERR);
		if (*code == MALLOC_ERR)
			return (free(process_cmd), MALLOC_ERR);
		else if (*code != 0)
			return (free(process_cmd), 0);
		else
		{
			if (!init_table(process_cmd, table))
				*code = run_pipeline(table) % 256;
			cleanup_table((t_command_table *)table);
		}
	}
	return (0);
}

int	new_prompt(t_command_table *table)
{
	char		*line;
	char		*process_cmd;
	static int	code = 0;
	char		*prompt_char;

	g_signal_received = 0;
	prompt_char = new_prompt_txt(table->env);
	if (!prompt_char)
		return (MALLOC_ERR);
	line = readline(prompt_char);
	free(prompt_char);
	if (g_signal_received)
	{
		if (g_signal_received == SIGINT)
			code = 130;
		g_signal_received = 0;
		return (0);
	}
	if (!line && !init_table(ft_strdup("exit"), table))
		run_pipeline(table);
	process_cmd = process_line(line, table->env, &code);
	return (handle_process_cmd(table, line, process_cmd, &code));
}

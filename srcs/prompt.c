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

char	*new_prompt_txt(char **env)
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

void	new_prompt(t_command_table *table)
{
	char		*line;
	char		*process_cmd;
	static int	code = 0;
	char		*prompt_char;

	g_signal_received = 0;
	prompt_char = new_prompt_txt(table->env);
	if (!prompt_char)
	{
		cleanup_arr((void **)table->env);
		cleanup_arr((void **)table->exp);
		error("malloc failed");
		exit(EXIT_FAILURE);
	}
	line = readline(prompt_char);
	free(prompt_char);
	if (g_signal_received)
	{
		if (g_signal_received == SIGINT)
			code = 130;
		g_signal_received = 0;
		return ;
	}
	if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
	{
		cleanup_arr((void **)table->env);
		cleanup_arr((void **)table->exp);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (ignore_prompt(line))
	{
		free(line);
		return ;
	}
	else if (ft_strcmp(line, "\n"))
		add_history(line);
	if (ft_strcmp(line, "\n") && ft_strcmp(line, "!") && ft_strcmp(line, ":"))
	{
		process_cmd = process_line(line, table->env, &code);
		free(line);
		if (!process_cmd)
		{
			return ;
		}
		if (code == MALLOC_ERR)
		{
			free(process_cmd);
			cleanup_arr((void **)table->env);
			cleanup_arr((void **)table->exp);
			error("malloc failed");
			exit(EXIT_FAILURE);
		}
		else if (code != 0)
		{
			free(process_cmd);
			return ;
		}
		else
		{
			if (!init_table(process_cmd, table))
				code = run_pipeline(table) % 255;
			cleanup_table((t_command_table *)table);
		}
	}
}

int	check_interrupt( void )
{
	if (g_signal_received)
		rl_done = 1;
	return (0);
}

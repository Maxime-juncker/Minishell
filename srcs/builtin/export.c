/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/21 18:18:27 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_export(char **argv)
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

static int	print_export(char **exp, int fd)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (exp[++i] != NULL)
	{
		ft_putstr_fd("export ", fd);
		j = 0;
		n = 0;
		while (exp[i][j])
		{
			ft_putchar_fd(exp[i][j], fd);
			if (exp[i][j] == '=' && !n)
			{
				ft_putchar_fd('"', fd);
				n++;
			}
			if (!exp[i][j + 1] && n)
				ft_putchar_fd('"', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

static int	check_arg(char *arg, int *append)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if ((!i && !ft_isalpha(arg[i]) && arg[i] != '_')
			|| (i && (!(ft_isalnum(arg[i]) || arg[i] == '_'
						|| arg[i] == '=' || (arg[i] == '+'
							&& arg[i + 1] == '=')))))
		{
			ft_putstr_fd("\033[0;31mminishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n\033[0m", 2);
			return (1);
		}
		i++;
	}
	if (!i)
		return (1);
	else if (!*append && (arg[i - 1] == '+' && arg[i] == '='))
		(*append)++;
	return (0);
}

int	export_cmd(t_command_table *table, t_command cmd)
{
	int		i;
	int		append;

	if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& table->n_commands)
		return (0);
	ft_sort_export(table->exp);
	if (cmd.n_args == 1)
		return (print_export(table->exp, cmd.fd_out), 0);
	i = 0;
	while (cmd.args[++i] != NULL)
	{
		append = 0;
		if (check_arg(cmd.args[i], &append))
			return (1);
		if (!append)
			unset_if_needed(table, cmd.args[i]);
		if (append && get_env_len(table->exp, cmd.args[i]) == -1 && !--append)
			cmd.args[i] = ft_strdup_except_char(cmd.args[i], '+');
		if (!cmd.args[i])
			return (MALLOC_ERR);
		export(table, cmd.args[i], append);
	}
	return (0);
}

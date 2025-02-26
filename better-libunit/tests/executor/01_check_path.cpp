#include "executor.hpp"
#include <iostream>
int	test_path( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);

	int code;
	init_table(process_line("ls -l", table.env, &code), &table);
	std::string path = get_cmd_path(get_paths(environ), table.commands[0]);
	if (path.compare("/usr/bin/ls") == 0)
		return (0);
	else
		return (1);
}
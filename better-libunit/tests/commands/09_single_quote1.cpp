#include "commands.hpp"

int	single_quote_basic( void )
{
	t_command_table	table;
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	int	code;

	init_table(process_line("echo \'$HOME\'", environ, &code), &table);
	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("$HOME\n") == 0)
		return (0);
	else
		return (1);
}
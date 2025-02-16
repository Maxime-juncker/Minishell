#include "commands.hpp"


int	ls_basic( void )
{
	t_command_table table;
	table.env = environ;

	init_table((char *)"ls", &table);

	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("\n") != 0)
		return (0);
	else
		return (1);
}

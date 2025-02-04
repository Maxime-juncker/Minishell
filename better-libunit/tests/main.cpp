/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:00:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/03 14:30:38 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.hpp"
#include "builtin/builtin.hpp"
#include "commands/commands.hpp"
#include "tests/tests.hpp"
#include "echo/echo.hpp"

int	main(void)
{
	executor_routine();
	built_in_routine();
//	commands_routine();
	tests_routine();
	echo_routine();
}

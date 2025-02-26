#include "tests.hpp"
#include "Routine.hpp"
#include "Test.hpp"
#include "libunit.hpp"

int	tests_routine( void )
{
	Libunit::Routine	routine("random tests");

	/* ================ ADD TESTS HERE ================ */
	routine.AddNewTest(Libunit::Test("syntax", ">", &synt_err_1));
	routine.AddNewTest(Libunit::Test("syntax", ">>", &synt_err_2));
	routine.AddNewTest(Libunit::Test("syntax", "<", &synt_err_3));
	routine.AddNewTest(Libunit::Test("syntax", "<<", &synt_err_4));
	routine.AddNewTest(Libunit::Test("syntax", "<>", &synt_err_5));
	routine.AddNewTest(Libunit::Test("syntax", ">>>>>", &synt_err_6));
	routine.AddNewTest(Libunit::Test("syntax", ">>>>>>>>>>>", &synt_err_7));
	routine.AddNewTest(Libunit::Test("syntax", "<<<<<<<<<<<", &synt_err_8));
	routine.AddNewTest(Libunit::Test("syntax", "> > > > >", &synt_err_9));
	routine.AddNewTest(Libunit::Test("syntax", ">>>> >> >> >>", &synt_err_10));
	routine.AddNewTest(Libunit::Test("syntax", "/", &synt_err_11));
	routine.AddNewTest(Libunit::Test("syntax", "//", &synt_err_12));
	routine.AddNewTest(Libunit::Test("syntax", "/./././...//", &synt_err_13));
	routine.AddNewTest(Libunit::Test("syntax", "///", &synt_err_14));
	routine.AddNewTest(Libunit::Test("syntax", "-", &synt_err_15));
	routine.AddNewTest(Libunit::Test("syntax", "|", &synt_err_16));
	routine.AddNewTest(Libunit::Test("syntax", "| test", &synt_err_17));
	routine.AddNewTest(Libunit::Test("syntax", "| | |", &synt_err_18));
	routine.AddNewTest(Libunit::Test("syntax", "||", &synt_err_19));
	routine.AddNewTest(Libunit::Test("syntax", "||||||||||", &synt_err_20));
	routine.AddNewTest(Libunit::Test("syntax", ">>|><", &synt_err_21));
	routine.AddNewTest(Libunit::Test("syntax", "\"hola\"", &synt_err_22));
	// routine.AddNewTest(Libunit::Test("syntax", "hola\'", &synt_err_23));
	routine.AddNewTest(Libunit::Test("syntax", "hola", &synt_err_24));
	routine.AddNewTest(Libunit::Test("syntax", "hola boula badaboum", &synt_err_25));
	routine.AddNewTest(Libunit::Test("syntax", "Makefile", &synt_err_26));
	routine.AddNewTest(Libunit::Test("syntax", "hola\"\"oui", &synt_err_27));
	routine.AddNewTest(Libunit::Test("syntax", "ho\"\'\'\"la\'\'oui", &synt_err_28));
	routine.AddNewTest(Libunit::Test("syntax", "\'\"hola\"\'", &synt_err_29));
	routine.AddNewTest(Libunit::Test("syntax", "\"\'hola\'\"", &synt_err_30));
	routine.AddNewTest(Libunit::Test("syntax", "\"\'\"ls\"\'\"", &synt_err_31));
	routine.AddNewTest(Libunit::Test("syntax", "\"\'\'\"/bin", &synt_err_32));
	routine.AddNewTest(Libunit::Test("syntax", "\"e\"\' c\'\"o\"\'h\'", &synt_err_33));
	routine.AddNewTest(Libunit::Test("syntax", "ls>1", &synt_err_34));
	routine.AddNewTest(Libunit::Test("syntax", "\"$HOGNGERbrknie\"", &synt_err_35));

	routine.AddNewTest(Libunit::Test("DOLLAR", "echo $?", &dolars_01));
	routine.AddNewTest(Libunit::Test("DOLLAR", "echo $?$?", &dolars_02));
	routine.AddNewTest(Libunit::Test("DOLLAR", "echo ?$DESKTOP_SESSION", &dolars_03));
	routine.AddNewTest(Libunit::Test("DOLLAR", "echo $", &dolars_04));
	routine.AddNewTest(Libunit::Test("DOLLAR", "echo $HOMEgfehgeuohge", &dolars_05));
	routine.AddNewTest(Libunit::Test("DOLLAR", "\"$HOMEgfehgeuohge\"", &dolars_06));
	routine.AddNewTest(Libunit::Test("DOLLAR", "$HOMEgfehgeuohge", &dolars_07));
	routine.AddNewTest(Libunit::Test("DOLLAR", "$DONTEXIST", &dolars_08));
	routine.AddNewTest(Libunit::Test("DOLLAR", "$DONTEXIST$VAR", &dolars_09));


	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}
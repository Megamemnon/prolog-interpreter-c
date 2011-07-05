#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "test_pltoken.h"
#include "test_plterm.h"
#include "test_plparse.h"
#include "test_plunify.h"

int main()
{
	WITH_COLOR(GREEN, printf("Tests begin\n"));

	test_pltoken();
	test_plterm();
	test_plparse();
	test_plunify();

	WITH_COLOR(GREEN, printf("Tests end\n"));
	return EXIT_SUCCESS;
}


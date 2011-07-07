#include "test_plinterpreter.h"

#define MAX_LINE 1024

FILE *open_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		WITH_COLOR(RED, printf("Could not open file: %s\n", filename));
		exit(1);
		return NULL;
	}
	return file;
}

void print_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		WITH_COLOR(RED, printf("Could not open file: %s\n", filename));
		exit(1);
	}

	char buf[MAX_LINE];
	while (fgets(buf, MAX_LINE, file)) {
		WITH_COLOR(YELLOW, printf("%s", buf));
	}

	printf("\n");
	fclose(file);
}

void test_interpret(const char *database_filename, const char *query_filename,
                   int resolves, const char *solution)
{
	WITH_COLOR(BLUE, printf("--------------------\n"));

	FILE *db_file = open_file(database_filename);
	FILE *query_file = open_file(query_filename);

	printf("Database:\n");
	print_file(database_filename);

	printf("Query:\n");
	print_file(query_filename);

	PLHandleInput(db_file, query_file);

	if (resolves) {
		WITH_COLOR(BLUE, printf("Should resolve with resolvent:\n"));
		WITH_COLOR(YELLOW, printf("%s\n", solution));
	} else {
		WITH_COLOR(BLUE, printf("Should not resolve\n"));
	}

	fclose(db_file);
	fclose(query_file);
}

void test_plinterpreter()
{
	WITH_COLOR(GREEN, printf("test_plinterpreter()\n"));
	//test_interpret("test_interpret_1_db.pl", "test_interpret_1_query.pl", 1, "add(s(0), s(0), s(s(0)))");
	test_interpret("test_interpret_2_db.pl", "test_interpret_2_query.pl", 1, "add(s(0), s(0), s(s(0)))");

}


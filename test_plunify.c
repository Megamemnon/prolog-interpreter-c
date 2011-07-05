#include "test_plunify.h"

PLTerm *load_term(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		WITH_COLOR(RED, printf("Could not open file: %s\n", filename));
		exit(1);
		return NULL;
	}

	PLToken *token = PLTokenise(file, 0);
	PLToken *remove = token;
	const PLToken *t = token;
	PLTerm *term = PLParse(&t);
	PLTokensFree(remove);
	fclose(file);
	return term;
}

void print_unifier(const PLUnifier *u)
{
	printf("{");
	while (u) {
		printf("%s = ", u->variable);
		PLTermPrint(u->term, stdout);
		printf(", ");
		u = u->next;
	}
	printf("}\n");
}

void test_unification(const char *filename1, const char *filename2, int should_unify, const char *correct_unifier)
{
	WITH_COLOR(BLUE, printf("--------------------\n"));

	PLTerm *t1 = load_term(filename1);
	PLTerm *t2 = load_term(filename2);

	printf("T1:\t");
	WITH_COLOR(YELLOW, PLTermPrint(t1, stdout));
	printf("T2:\t");
	WITH_COLOR(YELLOW, PLTermPrint(t2, stdout));
	printf("\n");

	PLUnifier *mgu;
	int status = PLUnify(t1, t2, &mgu);

	if (!status) {
		if (should_unify) {
			WITH_COLOR(GREEN, printf("Unifies\n"));
		} else {
			WITH_COLOR(RED, printf("Should not unify!\n"));
		}

		printf("Unified with MGU:\n");
		WITH_COLOR(YELLOW, print_unifier(mgu));

		printf("The correct MGU is:\n");
		WITH_COLOR(YELLOW, printf("%s\n", correct_unifier));
	} else {
		if (should_unify) {
			WITH_COLOR(RED, printf("Should unify with:\n"));
			WITH_COLOR(YELLOW, printf("%s\n", correct_unifier));
		} else {
			WITH_COLOR(GREEN, printf("Does not unify\n"));
		}
	}

	printf("\n");

	PLUnifierFree(mgu);
	PLTermFree(t1);
	PLTermFree(t2);
}

void test_plunify()
{
	WITH_COLOR(GREEN, printf("test_plunify()\n"));
	test_unification("unify_test_1.pl", "unify_test_1.pl", 1, "{}");
	test_unification("unify_test_1.pl", "unify_test_2.pl", 1, "{Number = 1}");
}

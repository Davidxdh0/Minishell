#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <stdio.h>
//eval "$(/Users/dyeboa/goinfre/.brew/bin/brew shellenv)"
TestSuite(printer);
Test(printer, basic)
{
    cr_redirect_stdout();

    fprintf(STDOUT_FILENO, "salut\n");
    cr_assert_stdout_eq_str("salut\n");	
}

Test(printer, print_stderr)
{
    cr_redirect_stderr();

    fprintf(STDERR_FILENO, "salut\n");
    cr_assert_stderr_eq_str("salut\n");
}
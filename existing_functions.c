#include "shell.h"

/**
 *env - print the present environement
 *@tkorder: order given
 *
 *Return: void
 */

void env(char **tkorder __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - leaves the shell
 * @tkorder: order given
 *
 * Return: void
 */

void quit(char **tkorder)
{
	int num_token = 0, arg;

	for (; tkorder[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free(tkorder);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_token == 2)
	{
		arg = _switchstr(tkorder[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tkorder[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tkorder);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}


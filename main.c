#include "shell.h"

/**
 * main - the shell's main code
 * @argc: count of all arguments given
 * @argv: gets argument ready to be described
 *
 * Return: 0 on success
 */


int main(int argc __attribute__((unused)), char **argv)
{
	char **commands = NULL;
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;
	char **current_token = NULL;
	int i, describe_token = 0;
	size_t n = 0;

	signal(SIGINT, control_handl);
	shell_name = argv[0];
	while (1)
	{
		irresponsive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			deleteline(line);
			delete_text(line);
			commands = tkmaker(line, ";");
		for (i = 0; commands[i] != NULL; i++)
		{
			current_token = tkmaker(commands[i], " ");
			if (current_token[0] == NULL)
			{
				free(current_token);
				break;
			}
			describe_token = desc_order(current_token[0]);
			initializer(current_token, describe_token);
			free(current_token);
		}
		free(commands);
	}
	free(line);
	return (status);
}


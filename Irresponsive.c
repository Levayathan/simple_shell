#include "shell.h"

/**
 * irresponsive - manages the irresponsive mode
 *
 * Return: void
 */

void irresponsive(void)
{
	char **current_token = NULL;
	int i, describe_token = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
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
		exit(status);
	}
}
#include "shell.h"

	static int status;

/**
 * commence - manages the executing of everything
 * @current_token: checks the present token
 * @describe_token: describe token
 *
 * Return: void
 */

void commence(char **current_token, int describe_token)
{
	pid_t PID;

	if (describe_token == EXTERNAL_COMMAND || describe_token == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			launch_order(current_token, describe_token);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		launch_order(current_token, describe_token);
}


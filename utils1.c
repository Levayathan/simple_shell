#include "shell.h"

/** desc_order - finds the command type
 * @order: the command to be described
 *
 * Return: the type of the command
 */

int desc_order(char *order)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_compare(order, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	path = look(order);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * launch_order - launches a command depending on it's type
 * @tkorder: token of the command
 * @order_type: command type
 *
 * Return: void
 */
void launch_order(char **tkorder, int order_type)
{
	void (*function)(char **order);

	if (order_type == EXTERNAL_COMMAND)
	{
		if (execve(tkorder[0], tkorder, NULL) == -1)
		{
			perror(val_env("PWD"));
			exit(2);
		}
	}
	if (order_type == PATH_COMMAND)
	{
		if (execve(look(tkorder[0]), tkorder, NULL) == -1)
		{
			perror(val_env("PWD"));
			exit(2);
		}
	}
	if (order_type == INTERNAL_COMMAND)
	{
		function = retri(tkorder[0]);
		function(tkorder);
	}
	if (order_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tkorder[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * look - looks for a command in the path
 * @order: command we using
 *
 * Return: the path we found command in, NULL if non existent
 */
char *look(char *order)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = val_env("PATH");
	int i;

	if (path == NULL || _lenght(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_lenght(path) + 1));
	_copy(path, path_cpy);
	path_array = tkmaker(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _concat(path_array[i], "/");
		temp = _concat(temp2, order);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * retri - gets a fuction based on command
 * @order: string we checking
 *
 * Return: pointer to the function, Null if non existent
 */
void (*retri(char *order))(char **)
{
	int i;
	command_link mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_compare(order, mapping[i].order_name) == 0)
			return (mapping[i].function);
	}
	return (NULL);
}

/**
 * val_env - retrieves the value of a variable environement
 * @env_name: name of the variable's environement
 *
 * Return: a string containing the value of the variable
 */
char *val_env(char *env_name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = env_name;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}
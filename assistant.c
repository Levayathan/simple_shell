#include "shell.h"

/**
 * tkmaker - turn input into a token and saves it
 *@inp: input to describe
 *@born: delimiter we using
 *
 *Return: array that saves the tokenized input
 */

char **tkmaker(char *inp, char *born)
{
	int num_delim = 0;
	char **av = NULL;
	char *token = NULL;
	char *point = NULL;

	token = _tkstring(inp, born, &point);

	while (token != NULL)
	{
		av = memchange(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
		av[num_delim] = token;
		token = _tkstring(NULL, born, &point);
		num_delim++;
	}

	av = memchange(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
	av[num_delim] = NULL;

	return (av);
}

/**
 *print - writes a string to the standard output
 *@strin: string to print
 *@river: output to print in
 *
 *Return: void
 */
void print(char *strin, int river)
{
	int i = 0;

	for (; strin[i] != '\0'; i++)
		write(river, &strin[i], 1);
}

/**
 *deleteline - delete the new line
 *@strg: string to delete the new line from
 *
 *
 *Return: void
 */

void deleteline(char *strg)
{
	int i = 0;

	while (strg[i] != '\0')
	{
		if (strg[i] == '\n')
			break;
		i++;
	}
	strg[i] = '\0';
}

/**
 *_copy - copies a string
 *@src: the array to copy from
 *@destination: the array to copy to
 *
 * Return: void
 */

void _copy(char *src, char *destination)
{
	int i = 0;

	for (; src[i] != '\0'; i++)
		destination[i] = src[i];
	destination[i] = '\0';
}

/**
 *_lenght - gets the length of a string
 *@strin: the string to be counted
 *
 * Return: the string lenght
 */

int _lenght(char *strin)
{
	int len = 0;

	if (strin == NULL)
		return (len);
	for (; strin[len] != '\0'; len++)
		;
	return (len);
}


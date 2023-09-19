#include "shell.h"


/**
 *_tkstring - make a token for a string
 *@strin: string to make token for
 *@born: delimiter we will use to tokenize the string
 *@point: pointer we will use to track the next token
 *
 *Return: The next token
 */
char *_tkstring(char *strin, char *born, char **point)
{
	char *finish;

	if (strin == NULL)
		strin = *point;

	if (*strin == '\0')
	{
		*point = strin;
		return (NULL);
	}

	strin += _lensub(strin, born);
	if (*strin == '\0')
	{
		*point = strin;
		return (NULL);
	}

	finish = strin + _countdiff(strin, born);
	if (*finish == '\0')
	{
		*point = finish;
		return (strin);
	}

	*finish = '\0';
	*point = finish + 1;
	return (strin);
}

/**
 * _switchstr - changes a string to an integer
 * @st: the string to be changed
 *
 * Return: the converted int
 */
int _switchstr(char *st)
{
	unsigned int n = 0;

	do {
		if (*st == '-')
			return (-1);
		else if ((*st < '0' || *st > '9') && *st != '\0')
			return (-1);
		else if (*st >= '0'  && *st <= '9')
			n = (n * 10) + (*st - '0');
		else if (n > 0)
			break;
	} while (*st++);
	return (n);
}

/**
 * memchange - gives a new location to the memory block
 * @pointer: pointer to the memory
 * @ancien: size of the pointer
 * @nouveau: new size of the memory to be allocated
 *
 * Return: pointer to the new memory block
 */
void *memchange(void *pointer, unsigned int ancien, unsigned int nouveau)
{
	void *temp_block;
	unsigned int i;

	if (pointer == NULL)
	{
		temp_block = malloc(nouveau);
		return (temp_block);
	}
	else if (nouveau == ancien)
		return (pointer);
	else if (nouveau == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}
	else
	{
		temp_block = malloc(nouveau);
		if (temp_block != NULL)
		{
			for (i = 0; i < min(ancien, nouveau); i++)
				*((char *)temp_block + i) = *((char *)pointer + i);
			free(pointer);
			return (temp_block);
		}
		else
			return (NULL);

	}
}

/**
 * control_handl - takes care of the signal of CTRL-C
 * @signl: signal number
 *
 * Return: void
 */
void control_handl(int signl)
{
	if (signl == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * delete_text - ignores all text after '#'
 * @inp1: the input we using
 *
 * Return: void
 */
void delete_text(char *inp1)
{
	int i = 0;

	if (inp1[i] == '#')
		inp1[i] = '\0';
	while (inp1[i] != '\0')
	{
		if (inp1[i] == '#' && inp1[i - 1] == ' ')
			break;
		i++;
	}
	inp1[i] = '\0';
}



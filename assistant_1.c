#include "shell.h"

/**
 *_compare - compare strings
 *@uno: first string
 *@dos: second string
 *
 * Return: differences between strings
 */

int _compare(char *uno, char *dos)
{
	int i = 0;

	while (uno[i] != '\0')
	{
		if (uno[i] != dos[i])
			break;
		i++;
	}
	return (uno[i] - dos[i]);
}

/**
 *_concat - assemble two strings content
 *@destination: string to put the result in
 *@src:  strings to assemble
 *
 * Return: address of the string
 */

char *_concat(char *destination, char *src)
{
	char *new_string =  NULL;
	int len_dest = _lenght(destination);
	int len_source = _lenght(src);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	_copy(destination, new_string);
	_copy(src, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}

/**
 *_lensub - figures the length of a substring
 *@tres: string to look in
 *@quatro: string to use
 *
 *Return: number of bytes
 */

int _lensub(char *tres, char *quatro)
{
	int i = 0;
	int match = 0;

	while (tres[i] != '\0')
	{
		if (_locchar(quatro, tres[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 *_countdiff - counts the caracters that exists in string 1 and not in 2
 *@str1: string to look in
 *@str2: string to use
 *
 *Return: return number of caracters that remains in string 2
 */


int _countdiff(char *str1, char *str2)
{
	int len = 0, i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (_locchar(str2, str1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *_locchar - finds a character inside a string
 *@st: string to look in
 *@c: char to look for
 *
 *Return: pointer to the first appearance of c in st
 */

char *_locchar(char *st, char c)
{
	int i = 0;

	for (; st[i] != c && st[i] != '\0'; i++)
		;
	if (st[i] == c)
		return (st + i);
	else
		return (NULL);
}


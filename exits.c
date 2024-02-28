#include "shell.h"

/**
 * _strncpy - A function that duplicates a string
 * up to a specified number of characters
 *
 * @dest: Destination for the copied string
 * @src: Original string to be copied
 * @n: Total number of characters in the original string
 * Return: To return the pointer to @dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int j;

	char *s = dest;

	for (j = 0; src[j] != '\0' && j < n - 1; j++)
	{
		dest[j] = src[j];
	}

	while (j < n)
	{
		dest[j++] = '\0';
	}

	return (s);
}

/**
 * _strncat - Function that concatenates two strings up to
 * a specified number of characters
 *
 * @dest: Destination to concatenated string
 * @src: The concatenated string
 * @n: The maximum number of characters taken from string
 * Return: To return a pointer to the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int j, k;

	char *s = dest;

	for (j = 0; dest[j] != '\0'; j++)
	{
	}

	for (k = 0; src[k] != '\0' && k < n; j++, k++)
	{
		dest[j] = src[k];
	}

	if (k < n)
	{
		dest[j] = '\0';
	}

	return (s);
}

/**
 * _strchr - A function that finds a specific character within a string
 *
 * @s: The string supplied to the function
 * @c: The character the function needs to find
 * Return: To return a pointer to the first occurrence of
 * the specific character within the string,
 * otherwise, returns NULL if the character isn't found in the string
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}



#include "shell.h"

/**
 * _eputs - Function that prints a string to stderr
 *
 * @str: The string to be printed
 * Return: Return void
 */

void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;

	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - Function that prints the character c
 * to the stderr
 * @c: Character to be printed to stderr
 *
 * Return: 1 if successful,
 * otherwise returns -1
 */

int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buf[j++] = c;

	return (1);
}

/**
 * _putfd - Function that inserts the character 'c' into
 * the supplied file descriptor named fd
 *
 * @c: Character to be printed
 * @fd: File descriptor to write to
 *
 * Return: 1 on success, or return -1 on failure
 */

int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buf[j++] = c;

	return (1);
}

/**
 * _putsfd - Function that displays a string to
 * the file descriptor named fd
 *
 * @str: String to be displayed
 * @fd: File descriptor to write to
 *
 * Return: To return the number of characters written
 */

int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str)
	{
		j += _putfd(*str++, fd);
	}

	return (j);
}

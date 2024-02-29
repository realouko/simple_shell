#include "shell.h"

/**
 * _erratoi - function that converts
 * a string into an integer
 *
 * @s: String to be converted
 * Return: 0 if the string contains no integers,
 * or else returns -1 if an error occurs
 */

int _erratoi(char *s)
{
	int j = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			result *= 10;
			result += (s[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_error - function that prints an error message on sdout
 *
 * @info: Structure containing the parameter and return information
 * @estr: string with the indicated error type
 *
 * Return: To return 0 if the string contains no integers,
 * otherwise returns -1 if an error occurs
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Function that converts a decimal integer
 * into a base ten number
 *
 * @input: decimal integer supplied as input
 * @fd: the file descriptor
 *
 * Return: To return the total characters printed out
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - A function that mimics the itoa
 * function from the Bourne Again Shell
 *
 * @num: integer number
 * @base: base for the integer number
 * @flags: warinings in case of an error
 *
 * Return: To return a string if successful
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do      {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - A function that changes the first occurence
 * of # to a 0
 *
 * @buf: address of the string to be changed
 * Return: Return 0
 */

void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}


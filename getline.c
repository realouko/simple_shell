#include "shell.h"

/**
 * input_buf - Function that reads chained commands
 * with buffers
 *
 * @info: Variable structure
 * @buf: Address for the buffer
 * @len: Address for the len variable
 *
 * Return: Returns the total bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif

		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);


			if (_strchr(*buf, ';'))
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}

	return (s);
}

/**
 * get_input - Function that removes the trailing from a line
 *
 * @info: Variable structure
 * Return: Return total number of bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);

		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Function that reads a buffer
 * and returns total bytes read
 *
 * @info: Variable structure
 * @buf: The buffer to be read by the function
 * @i: The size of the buffer read
 * Return: Return total numer of bytes read
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);

	s = read(info->readfd, buf, READ_BUF_SIZE);

	if (s >= 0)
		*i = s;

	return (s);

}


/**
 * _getline - Function that obtains the next
 * line of input from the standard inut
 *
 * @info: Variable structure
 * @ptr: Address to the allocated buffer
 * @length: Size of the allocated buffer
 * Return: Returns total number of bytes read from stdin
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Function that mimics the
 * ctr+c handler in Bourne again Shell
 *
 * @sig_num: Signal number
 * Return: No return
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


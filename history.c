#include "shell.h"

/**
 * get_history_file - Returns the history file path.
 * @info: Structure containing potential arguments.
 *
 * Return: Allocated string containing the history file path, or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;
	
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		free(dir);
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	
	return (buf);
}

/**
 * write_history - Appends history to a file or generates a new one.
 * @info: Structure containing potential arguments.
 *
 * Return: 1 upon success, -1 otherwise.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;
	
	if (!filename)
		return (-1);
	
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	
	if (fd == -1)
		return (-1);
	
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: Structure containing potential arguments.
 *
 * Return: The number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);
	
	if (!filename)
		return (0);
	
	fd = open(filename, O_RDONLY);
	free(filename);
	
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
	{
		close(fd);
		return (0);
	}
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	{
		close(fd);
		return (0);
	}
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
	{
		free(buf);
		close(fd);
		return (0);
	}
	close(fd);
	for (j = 0; j < fsize; j++)
	{
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	}
	if (last != j)
	{
		build_history_list(info, buf + last, linecount++);
	}
	free(buf);
	info->histcount = linecount;
	
	while (info->histcount-- >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
	}
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Creates a new entry in a history-linked list.
 * @info: Structure containing potential arguments.
 * @buf: Buffer containing the history entry.
 * @linecount: History line count.
 *
 * Return: 0 upon success.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;
	if (info->history)
	{
		node = info->history;
	}
	add_node_end(&node, buf, linecount);
	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
					

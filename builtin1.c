#include "shell.h"

/**
 * _myhistory - function to display the shell history
 * of commands in a numbered list starting from command number 0
 *
 * @info: Structure containing potential arguments,
 * used to maintain constant function prototype
 *  Return: Always 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function that sets the alias to string
 *
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, and 1 if an error occurs
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int retn;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	retn = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (retn);
}

/**
 * set_alias - a function that sets an alias to a string
 *
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 if an error occurs
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias to a string
 *
 * @node: the alias node
 * Return: Always 0 on success, and 1 if an error occurs
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - a function that mimics the builtin alias
 * from the Bourne Again Shell
 *
 * @info: A structure containing potential arguments that
 * is used to maintain a constant function prototype
 *  Return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}


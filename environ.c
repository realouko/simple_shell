#include "shell.h"

/**
 * _myenv - Function that prints the environment variables
 *
 * @info: Structure containing the function prototype and
 * the arguments it accepts
 *
 * Return: Always 0.
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Function that gets the value of an environment variable
 *
 * @info: A structure containing potential arguments for function
 * @name: Environment variable name
 *
 * Return: Returns the value of the environment variable,
 * otherwise returns NULL if environment variable is not found
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);

		node = node->next;
	}

	return (NULL);
}

/**
 * _mysetenv - Function that initializes or modifies a new environment variable
 *
 * @info: A structure with potential arguments for the function
 * Return: 1 on success, or 0 upon failure
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (0);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (1);

	return (0);
}

/**
 * _myunsetenv - Function that unsets environment variables
 * @info: A structure containing potential argument for the function
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * populate_env_list - Function that populates the
 * environment linked list
 * @info: A structure containing potential arguments
 * for the function
 *
 * Return: Always 0.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);

	info->env = node;
	return (0);
}



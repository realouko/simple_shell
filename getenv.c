#include "shell.h"

/**
 * get_environ - A function that returns a duplicate of
 * the string array from the environment
 *
 * @info: A structure containing potential arguments
 * for the function
 * Return: To return the pointer to the
 * duplicated string array from the environment
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return info->environ;
}

/**
 * _unsetenv - Function that deletes an environment variable
 *
 * @info: A structure containing potential arguments to the function
 * @var: The variable to be deleted
 * Return: To return 1 if successful, or 0 if unsuccesful
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *p;

	if (!node || !var)
		return 0;

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}

	return info->env_changed;
}

/**
 * _setenv - A function that creates or modifies
 * an environment variable
 *
 * @info: A structure containing potential arguments to the function
 * @var: The environment variable to be created or modified by setenv
 * @value: New value assigned to the environment variable
 * Return: To return 0 if successful, or 1 if unsuccesful
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return 0;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return 1;

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return 0;
}

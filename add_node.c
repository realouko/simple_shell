#include "shell.h"
#include <stdlib.h>

/**
 * add_node_end - Adds a new node
 * with a string at the end of a linked list
 * @head: Pointer to the pointer to the head of the linked list
 * @str: String to be added to the new node
 * @num: Number to be added to the new node
 *
 * Return: Pointer to the newly added node,
 * or NULL on failure
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last = *head;

	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->str = strdup(str);
	new_node->num = num;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	} else
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_node;
	}
	return (new_node);
}


#include "shell.h"

/**
 * delete_node_at_index - Deletes a node
 * at a specified index in a linked list
 * @head: Pointer to the pointer to
 * the head of the linked list
 * @index: Index of the node to be deleted
 *
 * Return: 0 on success, or -1 if the
 * node at the index does not exist
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int i;

	list_t *current;
	list_t *next;
	current = *head;
	if (*head == NULL)
		return (-1);
	for (i = 0; current != NULL && i < index - 1; i++)
	{
		current = current->next;
	}
	if (current == NULL || current->next == NULL)
		return (-1);
	next = current->next->next;
	free(current->next->str);
	free(current->next);
	current->next = next;
	return (0);
}


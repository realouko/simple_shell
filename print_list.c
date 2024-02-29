#include "shell.h"
#include <stdio.h>

/**
 * print_list_str - Prints the contents
 * of a linked list of strings
 * @head: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the list
 */
size_t print_list_str(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;
	
	while (current != NULL)
	{
		printf("%s\n", current->str);
		current = current->next;
		count++;
	}
	return (count);
}


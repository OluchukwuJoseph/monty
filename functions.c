#include "monty.h"

int error = 0;
instruction_t action;

/**
 * ruc - This function creates a new string by removing unwanted characters
 * specified in the 'unwanted_characters' string
 * @string: String from which unwanted characters are to be removed
 * @unwanted_characters: string containing characters to be removed from string
 * Return: A string containing 'string' without the unwanted characters
 * (memory must be freed by the caller)
 * Return NULL if memory allocation failed
 */
char *ruc(char *string, char *unwanted_characters);
char *ruc(char *string, char *unwanted_characters)
{
	size_t length = 0, i, j, k = 0;
	int equal;
	char *new_string = NULL;

	if (string == NULL)
		return (NULL);
	if (unwanted_characters == NULL)
		return (string);
	/*Count the characters in 'string' excluding unwanted characters*/
	for (i = 0; string[i] != '\0'; i++)
	{
		equal = 0;
		for (j = 0; unwanted_characters[j] != '\0'; j++)
		{
			if (string[i] == unwanted_characters[j])
			{
				equal = 1;
				break;
			}
		}
		if (equal == 1)
			continue;
		length++;
	}

	new_string = malloc(sizeof(char) * (length + 1));
	if (new_string == NULL)
		return (NULL);
	/*Copy 'string' to 'new_string' excluding unwanted characters*/
	for (i = 0; string[i] != '\0'; i++)
	{
		equal = 0;
		for (j = 0; unwanted_characters[j] != '\0'; j++)
		{
			if (string[i] == unwanted_characters[j])
			{
				equal = 1;
				break;
			}
		}
		if (equal == 1)
			continue;
		new_string[k++] = string[i];
	}
	new_string[k] = '\0';
	return (new_string);
}


/**
 * _strcom - This function compares two strings and determines their equality
 * or partial match based on the specified tolerance level.
 * @string: Pointer to the first string for comparison
 * @target: Pointer to the second string for comparison
 * @tolerance: Tolerance level for string comparison
 * (0 for exact match, 1 for partial match)
 * Return: 0 if Strings are equal
 * positive integer if Number of characters in string is beyond target
 * -1 if Strings are not equal, and tolerance is set to 0
 */
int compare_strings(char *string, char *target, int tolerance)
{
	size_t i, length1, j = 0;

	if (strlen(string) != strlen(target) && tolerance == 0)
		return (-1);

	length1 = strlen(string);
	for (i = 0; i < length1; i++)
	{
		if (string[i] != target[i])
		{
			if (i < strlen(target) - 1)
				return (-1);
		}
		/*Break if end of 'target' is reached*/
		if (i > (strlen(target) - 1))
			break;
		/*If the entire strings are equal, return 0*/
		if (i == (strlen(target) - 1) && strlen(string) == strlen(target))
			return (0);
	}
	/*Count characters in 'string' beyond the matching portion with 'target'*/
	i = strlen(target);
	for (; string[i] != '\0'; i++)
		j++;
	return (j);
}

void (*find_command(char *command))(stack_t **stack, unsigned int line_number)
{
	char *command_copy = strdup(command);

	if (compare_strings(command_copy, "pall", 0) == 0)
	{
		action.opcode = command_copy;
		return (&pall);
	}
	else if (compare_strings(command_copy, "push", 1) != -1)
	{
		action.opcode = command_copy;
		return (&push);
	}
	else
	{
		free(command_copy);
		error = 1;
	}
	return (NULL);
}

void free_linked_list(stack_t *stack)
{
	stack_t *temp;

	temp = stack;
	while (stack != NULL)
	{
		stack = stack->next;
		free(temp);
		temp = stack;
	}
}
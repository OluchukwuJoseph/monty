#include "monty.h"

instruction_t action;
int error = 0;

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
 * compare_strings - This function compares two strings and determines their
 * equality or partial match based on the specified tolerance level.
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
	if (length1 == 0)
		return (-1);

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

/**
 * find_command - Locates the corresponding function for a given command.
 * @command: A pointer to a string representing the command to be found.
 * Return: A function pointer to the identified command function.
 * If the command is not recognized, returns NULL.
 */
void (*find_command(char *command))(stack_t **stack, unsigned int line_number);
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
	else if (compare_strings(command_copy, "pop", 0) == 0)
	{
		action.opcode = command_copy;
		return (&pop);
	}
	else if (compare_strings(command_copy, "add", 0) == 0)
	{
		action.opcode = command_copy;
		return (&add);
	}
	else if (compare_strings(command_copy, "nop", 0) == 0)
	{
		action.opcode = command_copy;
		return (&nop);
	}
	else if (compare_strings(command_copy, "swap", 0) == 0)
	{
		action.opcode = command_copy;
		return (&swap);
	}
	else if (compare_strings(command_copy, "pint", 0) == 0)
	{
		action.opcode = command_copy;
		return (&pint);
	}
<<<<<<< HEAD
	else if (compare_strings(command_copy, "sub", 0) == 0)
	{
		action.opcode = command_copy;
		return (&sub);
	}
	else if (compare_strings(command_copy, "mul", 0) == 0)
	{
		action.opcode = command_copy;
		return (&mul);
	}
	else if (compare_strings(command_copy, "div", 0) == 0)
	{
		action.opcode = command_copy;
		return (&_div);
	}
	else if (compare_strings(command_copy, "mod", 0) == 0)
	{
		action.opcode = command_copy;
		return (&mod);
	}
=======
	else if (compare_strings(command_copy, "mod", 0) == 0)
        {
                action.opcode = command_copy;
                return (&mod);
        }
	else if (compare_strings(command_copy, "my_div", 0) == 0)
        {
                action.opcode = command_copy;
                return (&my_div);
        }
>>>>>>> 1f06b156cf1334ca3c1b525f909bc8d1e1255709
	else
	{
		free(command_copy);
		error = 1;
	}
	return (NULL);
}

/**
 * free_linked_list - Frees the memory occupied by a linked list.
 * @stack: A pointer to the head of the linked list to be freed.
 * Return: Nothing
 */
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

/**
 * extract_characters_after_push - Extracts characters from the input
 * string after a specified target substring.
 * @string: String from which characters will be extracted.
 * @target: target substring after which characters will be extracted.
 * @line_n: Line Number
 * Return: A string containing characters after the target substring.
 * Return NULL If memory allocation fails.
 * Return NULL if non-numeric character is found after push
 */
char *extract_characters_after_push(char *string, char *target, size_t line_n)
{
	int i = strlen(target);
	int j, length = 0;
	char *new_string = NULL;

	for (; string[i] != '\0'; i++)
	{
		/*Check if the character is not between 1 and 9*/
		if ((string[i] >= '0' && string[i] <= '9')
				|| (string[i] == '-' &&
					(string[i + 1] >= '0' &&
					 string[i + 1] <= '9')))
			length++;
		else
		{
			fprintf(stderr, "L%lu: usage: push integer\n", line_n);
			return (NULL);
		}
	}

	new_string = (char *)malloc(sizeof(char) * (length + 1));
	if (new_string == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (NULL);
	}
	i = strlen(target);
	/*Copy characters from the input string to the new string.*/
	for (j = 0; string[i] != '\0'; j++, i++)
		new_string[j] = string[i];
	new_string[j] = '\0';
	return (new_string);
}


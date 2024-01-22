#include "monty.h"

/**
 * main - The main function for a Monty interpreter
 * that reads and executes Monty bytecode from a file.
 * @ac: The number of command-line arguments.
 * @av: An array of pointers to strings representing the command-line arguments
 * Return: 0 on successful execution.
 * Otherwise return 1
 */
int main(int ac, char **av);
int main(int ac, char **av)
{
	FILE *file;
	ssize_t length;
	size_t len, line_number = 1;
	char *line_content = NULL, *command = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(av[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		length = len = 0;
		length = getline(&line_content, &len, file);
		if (length == -1)
			break;
		line_content[length - 1] = '\0';
		if (line_content[0] == '#')
		{
			free(line_content);
			continue;
		}
		command = ruc(line_content, " $\n");
		if (command == NULL)
		{
			free(line_content);
			exit(EXIT_FAILURE);
		}
		action.f = find_command(command);
		if (error == 1)
		{
			fprintf(stderr, "L%lu: unknown instruction %s\n", line_number, command);
			free(command);
			free(line_content);
			if (stack != NULL)
				free_linked_list(stack);
			exit(EXIT_FAILURE);
		}
		action.f(&stack, line_number);
		if (error == 1)
		{
			free(action.opcode);
			free(command);
			free(line_content);
			if (stack != NULL)
				free_linked_list(stack);
			fclose(file);
			exit(EXIT_FAILURE);
		}
		error = 0;
		line_number++;
		free(action.opcode);
		free(line_content);
		free(command);
	}
	free(line_content);
	fclose(file);
	free_linked_list(stack);
	return (0);
}

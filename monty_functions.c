#include "monty.h"

stack_t *stack = NULL;

void pall(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *temp;

	temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

void push(stack_t **stack, unsigned int line_number)
{
	int result, i, j, num;
	char *num_string = NULL;
	stack_t *temp;

	result = compare_strings(action.opcode, "push", 1);
	if (result == 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		error = 1;
	}
	else
	{
		num_string = (char *)malloc(sizeof(char) * (result + 1));
		if (num_string == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			error = 1;
		}

		i = strlen(action.opcode) - result;
		for (j = 0; action.opcode[i] != '\0'; j++, i++)
			num_string[j] = action.opcode[i];
		num_string[j] = '\0';

		num = atoi(num_string);
		free(num_string);
		temp = (stack_t *)malloc(sizeof(stack_t));
		if (temp == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			error = 1;
		}
		temp->n = num;
		temp->prev = NULL;
		temp->next = NULL;

		if (*stack == NULL)
			*stack = temp;
		else
		{
			temp->next = *stack;
			(*stack)->prev = temp;
			*stack = temp;
		}
	}
}


#include "monty.h"

/**
 * stack_length - Calculates the length of a stack
 * @stack: Stack's length to be calculated
 * Return: Length of stack;
 */
int stack_length(stack_t *stack)
{
	stack_t *temp;
	int length = 0;

	if (stack == NULL)
		return (0);

	temp = stack;
	while (temp != NULL)
	{
		length++;
		temp = temp->next;
	}
	return (length);
}

/**
 * add - adds the first 2 elements of a stack
 * @stack: A pointer to the head of a stack
 * @line_number: Current line number
 * Return: Nothing
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;
	int length_of_stack = stack_length(*stack);

	if (length_of_stack < 2)
	{
		fprintf(stderr, "L<%u>: can't add, stack too short\n", line_number);
		error = 1;
	}
	else
	{
		temp = (*stack)->next;
		temp->n = temp->n + (*stack)->n;
		temp->prev = NULL;
		free(*stack);
		*stack = temp;
	}
}

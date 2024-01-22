#include "monty.h"

/**
 * mod - adds the first 2 elements of a stack
 * @stack: A pointer to the head of a stack
 * @line_number: Current line number
 * Return: Nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;
	int length_of_stack = stack_length(*stack);

	if (length_of_stack < 2)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		error = 1;
	}
	else
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			error = 1;
		}
		else
		{
			temp = (*stack)->next;
			temp->n = temp->n % (*stack)->n;
			temp->prev = NULL;
			free(*stack);
			*stack = temp;
		}
	}
}


/**
 * my_div - divides the first 2 elements of a stack
 * @stack: A pointer to the head of a stack
 * @line_number: Current line number
 * Return: Nothing
 */
void my_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;
	int length_of_stack = stack_length(*stack);

	if (length_of_stack < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		error = 1;
	}
	else
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			error = 1;
		}
		else
		{
			temp = (*stack)->next;
			temp->n = temp->n / (*stack)->n;
			temp->prev = NULL;
			free(*stack);
			*stack = temp;
		}
	}
}

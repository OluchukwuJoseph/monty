#include "monty.h"

stack_t *stack = NULL;

/**
 * pall - Prints all elements in the stack.
 * @stack: A pointer to the head of the stack to be printed.
 * @line_number: Line number
 * Return: Nothing
 */
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

/**
 * push - Pushes an integer onto the top of the stack.
 * @stack: A pointer to the head of the stack.
 * @line_number: Line number.
 * Return: Nothing
 */
void push(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number)
{
	int result, num;
	char *num_s = NULL;
	stack_t *temp;

	/*Check for valid usage of the "push" command*/
	result = compare_strings(action.opcode, "push", 1);
	if (result == 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		error = 1;
	}
	else
	{
		num_s = extract_characters_after_push(action.opcode, "push", line_number);
		if (num_s == NULL)
			error = 1;
		else
		{
			/*Convert the string to an integer.*/
			num = atoi(num_s);
			free(num_s);
			/*Push the new node onto the stack.*/
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
}

/**
 * pop - Pops an integer oot of the stack.
 * @stack: A pointer to the head of the stack.
 * @line_number: Line number.
 * Return: Nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		error = 1;
	}
	else
	{
		temp = *stack;
		*stack = (*stack)->next;
		(*stack)->prev = NULL;
		free(temp);
	}
}


/**
 * swap -  swaps the top two elements of the stack.
 * @stack: A pointer to the head of the stack.
 * @line_number: Line number.
 * Return: Nothing.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;
	int length_of_stack = stack_length(*stack);

	if (length_of_stack < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n",
				line_number);
		/*main function will check the value of error and*/
		/* exit with failure if error is 1*/
		error = 1;
	}
	else
	{
		/*set temp to the next node (node 2)*/
		temp = (*stack)->next;
		/*set stack to temp (node 2)*/
		*stack = temp;
		/*set temp to node 1*/
		temp = temp->prev;
		/*set node 1's prev to node 2*/
		/*This is where the swapping takes place*/
		temp->prev = *stack;
		/*set node 1 next to node 2 next*/
		temp->next = (*stack)->next;
		/*set node 2 next to node 1*/
		(*stack)->next = temp;
		/*set node 2 prev to NULL since*/
		/*node 2 is now the head of the stack*/
		(*stack)->prev = NULL;
	}
}

/**
 * pint - prints the value at the top of the stack, followed by a new line.
 * @stack: A pointer to the head of the stack.
 * @line_number: Line number.
 * Return: Nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		error = 1;
	}
	else
	{
		temp = *stack;
		printf("%d\n", temp->n);
	}
}

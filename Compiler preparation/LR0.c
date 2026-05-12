#include <stdio.h>
#include <string.h>

char stack[20], input[20];
int top = -1;
int i = 0;

// Push symbol into stack
void push(char ch)
{
    stack[++top] = ch;
    stack[top + 1] = '\0';
}

// Perform reductions
int reduce()
{
    // Rule: A -> b
    if (stack[top] == 'b')
    {
        stack[top] = 'A';
        printf("%s\t%s\tReduce A->b\n", stack, &input[i]);
        return 1;
    }

    // Rule: A -> aA
    if (top >= 1 && stack[top - 1] == 'a' && stack[top] == 'A')
    {
        top--;
        stack[top] = 'A';
        stack[top + 1] = '\0';

        printf("%s\t%s\tReduce A->aA\n", stack, &input[i]);
        return 1;
    }

    // Rule: S -> AA
    if (top >= 1 && stack[top - 1] == 'A' && stack[top] == 'A')
    {
        top--;
        stack[top] = 'S';
        stack[top + 1] = '\0';

        printf("%s\t%s\tReduce S->AA\n", stack, &input[i]);
        return 1;
    }

    return 0;
}

int main()
{
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");

    while (input[i] != '\0')
    {
        // Shift operation
        push(input[i]);

        printf("%s\t%s\tShift %c\n",
               stack,
               &input[i],
               input[i]);

        i++;

        // Apply reductions repeatedly
        while (reduce());
    }

    // Final reductions after input ends
    while (reduce());

    // Check acceptance
    if (strcmp(stack, "S") == 0)
        printf("%s\t\tAccepted\n", stack);
    else
        printf("%s\t\tRejected\n", stack);

    return 0;
}
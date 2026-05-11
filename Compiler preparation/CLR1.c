#include <stdio.h>
#include <string.h>

char input[100];
char stack[100];
int top = -1;
int i = 0;

void push(char ch)
{
    stack[++top] = ch;
}

void pop()
{
    if(top >= 0)
        top--;
}

int parseA()
{
    while(input[i] == 'a')
    {
        push('a');
        i++;
    }

    if(input[i] == 'b')
    {
        while(top != -1)
            pop();

        i++;
        return 1;
    }

    return 0;
}

int parseS()
{
    if(parseA() && parseA())
    {
        if(input[i] == '\0')
            return 1;
    }
    return 0;
}

int main()
{
    printf("Grammar: S -> AA\n");
    printf("A -> aA | b\n");

    printf("Enter string: ");
    scanf("%s", input);

    if(parseS())
        printf("String Accepted by CLR(1)\n");
    else
        printf("String Rejected\n");

    return 0;
}
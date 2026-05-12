#include<stdio.h>
#include<string.h>

#define MAX 20

char lhs[MAX][10], rhs[MAX][50];
int n;

// Function to check whether variable is used later
int isUsed(char var[], int start)
{
    int i;
    for(i = start; i < n; i++)
    {
        if(strstr(rhs[i], var))
            return 1;
    }
    return 0;
}

int main()
{
    int i, j;
    char stmt[50];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter statement %d: ", i + 1);
        scanf("%s", stmt);

        sscanf(stmt, "%[^=]=%s", lhs[i], rhs[i]);
    }

    // Optimization logic
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(strcmp(rhs[i], rhs[j]) == 0)
            {
                strcpy(rhs[j], rhs[i]);
            }
        }
    }

    printf("\nOptimized Code:\n");

    for(i = 0; i < n; i++)
    {
        if(isUsed(lhs[i], i + 1) || i == n - 1)
        {
            printf("%s = %s\n", lhs[i], rhs[i]);
        }
    }

    return 0;
}
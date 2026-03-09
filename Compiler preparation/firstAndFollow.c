#include<stdio.h>
#include<ctype.h>
#include<string.h>

char prod[10][10];
int n;

void first(char c)
{
    int i;

    if(!isupper(c))
    {
        printf("%c ",c);
        return;
    }

    for(i=0;i<n;i++)
    {
        if(prod[i][0]==c)
        {
            if(!isupper(prod[i][3]))
                printf("%c ",prod[i][3]);
            else
                first(prod[i][3]);
        }
    }
}

void follow(char c)
{
    int i,j;

    if(prod[0][0]==c)
        printf("$ ");

    for(i=0;i<n;i++)
    {
        for(j=3;j<strlen(prod[i]);j++)
        {
            if(prod[i][j]==c)
            {
                if(prod[i][j+1]!='\0')
                    first(prod[i][j+1]);
                else
                    follow(prod[i][0]);
            }
        }
    }
}

int main()
{
    int i;

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions:\n");
    for(i=0;i<n;i++)
        scanf("%s",prod[i]);

    printf("\n----------------------------------\n");
    printf("| Non-Terminal | FIRST | FOLLOW |\n");
    printf("----------------------------------\n");

    for(i=0;i<n;i++)
    {
        printf("|   %c   | { ",prod[i][0]);
        first(prod[i][0]);
        printf("} | { ");
        follow(prod[i][0]);
        printf("} |\n");
    }

    printf("----------------------------------\n");

    return 0;
}
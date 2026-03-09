#include<stdio.h>
#include<string.h>

int main()
{
    int ntcount;
    printf("Enter number of non-terminals: ");
    scanf("%d",&ntcount);

    char nt[ntcount];
    int prodcount[ntcount];
    char prod[ntcount][10][50];

    for(int i=0;i<ntcount;i++)
    {
        printf("\nEnter non-terminal %d: ",i+1);
        scanf(" %c",&nt[i]);

        printf("Enter number of productions for %c: ",nt[i]);
        scanf("%d",&prodcount[i]);

        for(int j=0;j<prodcount[i];j++)
        {
            printf("Enter production %d: ",j+1);
            scanf("%s",prod[i][j]);
        }
    }

    printf("\nAfter Left Factoring:\n");

    for(int i=0;i<ntcount;i++)
    {
        char prefix[50];
        int k=0;

        while(prod[i][0][k] != '\0')
        {
            char c = prod[i][0][k];
            int flag=1;

            for(int j=1;j<prodcount[i];j++)
            {
                if(prod[i][j][k] != c)
                {
                    flag=0;
                    break;
                }
            }

            if(flag)
            {
                prefix[k]=c;
                k++;
            }
            else
                break;
        }

        prefix[k]='\0';

        if(k==0)
        {
            printf("%c->",nt[i]);
            for(int j=0;j<prodcount[i];j++)
            {
                printf("%s",prod[i][j]);
                if(j!=prodcount[i]-1)
                    printf("|");
            }
            printf("\n");
        }
        else
        {
            printf("%c->%s%c'\n",nt[i],prefix,nt[i]);

            printf("%c'->",nt[i]);

            for(int j=0;j<prodcount[i];j++)
            {
                printf("%s",prod[i][j]+k);
                if(j!=prodcount[i]-1)
                    printf("|");
            }
            printf("\n");
        }
    }

    return 0;
}
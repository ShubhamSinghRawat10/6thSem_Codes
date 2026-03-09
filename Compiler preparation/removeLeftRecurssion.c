#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int ntcount;
    printf("Enter the no. of non terminals: ");
    scanf("%d",&ntcount);

    int prodcount[ntcount];
    char nt[ntcount];
    char prod[ntcount][10][50];

    for(int i=0;i<ntcount;i++)
    {
        printf("Enter the non-terminal %d: ",i+1);
        scanf(" %c",&nt[i]);

        printf("Enter the no. of productions for %c: ",nt[i]);
        scanf("%d",&prodcount[i]);

        for(int j=0;j<prodcount[i];j++)
        {
            printf("Enter production %d for %c: ",j+1,nt[i]);
            scanf("%s",prod[i][j]);
        }
    }

    printf("\nAfter removing left recursion:\n");

    for(int i=0;i<ntcount;i++)
    {
        int acount=0,bcount=0;
        char alpha[10][50],beta[10][50];

        for(int j=0;j<prodcount[i];j++)
        {
            if(nt[i]==prod[i][j][0])
                strcpy(alpha[acount++],prod[i][j]+1);
            else
                strcpy(beta[bcount++],prod[i][j]);
        }

        if(acount==0)
        {
            printf("%c->",nt[i]);
            for(int k=0;k<bcount;k++)
            {
                printf("%s",beta[k]);
                if(k!=bcount-1) printf("|");
            }
            printf("\n");
        }
        else
        {
            printf("%c->",nt[i]);
            for(int k=0;k<bcount;k++)
            {
                printf("%s%c'",beta[k],nt[i]);
                if(k!=bcount-1) printf("|");
            }
            printf("\n");

            printf("%c'->",nt[i]);
            for(int k=0;k<acount;k++)
            {
                printf("%s%c'|",alpha[k],nt[i]);
            }
            printf("e\n");
        }
    }
}
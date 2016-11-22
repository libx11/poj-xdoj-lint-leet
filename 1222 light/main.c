#include <stdio.h>
#include <string.h>

void debug(int a[7][8])
{
    int i, j;
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 8; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void c(int light[7][8], int x, int y)
{
    if(0 == light[x][y])
        light[x][y] = 1;
    else if(1 == light[x][y])
        light[x][y] = 0;

    if(0 == light[x+1][y])
        light[x+1][y] = 1;
    else if(1 == light[x+1][y])
        light[x+1][y] = 0;

    if(0 == light[x-1][y])
        light[x-1][y] = 1;
    else if(1 == light[x-1][y])
        light[x-1][y] = 0;

    if(0 == light[x][y-1])
        light[x][y-1] = 1;
    else if(1 == light[x][y-1])
        light[x][y-1] = 0;

    if(0 == light[x][y+1])
        light[x][y+1] = 1;
    else if(1 == light[x][y+1])
        light[x][y+1] = 0;
}

int main()
{
    int i, j, n, count, check, l[6], light[7][8], temp[7][8], buttom[5][6];
    memset(light, -1, 8*7*sizeof(int));

    scanf("%d", &n);

    for(count = 1; count <= n; count++)
    {
        for(i = 1; i < 6; i++)
            for(j = 1; j < 7; j++)
                scanf("%d", &light[i][j]);


        for(l[0] = 0; l[0] < 2; l[0]++)
            for(l[1] = 0; l[1] < 2; l[1]++)
                for(l[2] = 0; l[2] < 2; l[2]++)
                    for(l[3] = 0; l[3] < 2; l[3]++)
                        for(l[4] = 0; l[4] < 2; l[4]++)
                            for(l[5] = 0; l[5] < 2; l[5]++)
                            {
//                                debug(light);
                                memset(buttom, 0, 5*6*sizeof(int));
                                memcpy(temp, light, 8*7*sizeof(int));
                                for(i = 0; i < 6; i++)
                                    if(1 == l[i])
                                    {
                                        c(temp, 1, i+1);
                                        buttom[0][i] = 1;
                                    }

                                for(i = 1; i < 5; i++)
                                    for(j = 1; j < 7; j++)
                                        if(1 == temp[i][j])
                                        {
                                            buttom[i][j-1] = 1;
                                            c(temp, i+1, j);
                                        }
                                check = 1;
                                for(i = 1; i < 7; i++)
                                    if(1 == temp[5][i])
                                        check = 0;
                                if(1 == check)
                                {
                                    printf("PUZZLE #%d\n", count);
                                    for(i = 0; i < 5; i++)
                                    {
                                        for(j = 0; j < 6; j++)
                                            printf("%d ", buttom[i][j]);
                                        printf("\n");
                                    }
                                    goto L;
                                }
                            }
    L:;}
    return 0;
}

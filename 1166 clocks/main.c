#include <stdio.h>

void search(int *ind, int mat[], int r[][9])
{
    int i, check;
    for(ind[0] = 0; ind[0] < 4 ; ind[0]++)
        for(ind[1] = 0; ind[1] < 4; ind[1]++)
            for(ind[2] = 0; ind[2] < 4; ind[2]++)
                for(ind[3] = 0; ind[3] < 4; ind[3]++)
                    for(ind[4] = 0; ind[4] < 4; ind[4]++)
                        for(ind[5] = 0; ind[5] < 4; ind[5]++)
                            for(ind[6] = 0; ind[6] < 4; ind[6]++)
                                for(ind[7] = 0; ind[7] < 4; ind[7]++)
                                    for(ind[8] = 0; ind[8] < 4; ind[8]++)
                                    {
                                        check = 1;
                                        for(i = 0; i < 9; i++)
                                        {
                                            if(0 != (mat[i]+ind[0]*r[0][i] + ind[1]*r[1][i] + ind[2]*r[2][i]
                                                     + ind[3]*r[3][i] + ind[4]*r[4][i] + ind[5]*r[5][i]
                                                    + ind[6]*r[6][i] + ind[7]*r[7][i] + ind[8]*r[8][i]) % 4 )
                                            {
                                                check = 0;
                                            }
                                        }
                                        if(1 == check)
                                            return;
                                    }
}

int main()
{
    int r[9][9] = {{1,1,0,1,1,0,0,0,0},{1,1,1,0,0,0,0,0,0},{0,1,1,0,1,1,0,0,0},
                    {1,0,0,1,0,0,1,0,0},{0,1,0,1,1,1,0,1,0},{0,0,1,0,0,1,0,0,1},
                    {0,0,0,1,1,0,1,1,0},{0,0,0,0,0,0,1,1,1},{0,0,0,0,1,1,0,1,1}};
    int i, num, matrix[9], ind[9] = {0};

    for(i = 0; i < 9; i++)
        scanf("%d", &matrix[i]);

    search(ind, matrix, r);

    for(i = 0; i < 9; i++)
        if(ind[i] != 0)
            num = i;
    for(i = 0; i < num; i++)
    {
        while(ind[i] > 0)
        {
            printf("%d ",i+1);
            ind[i]--;
        }
    }
    while(ind[num] > 1)
    {
        printf("%d ",num+1);
        ind[num]--;
    }
    printf("%d\n", num+1);

    return 0;
}

#include <stdio.h>
#include <string.h>
#define lake_sum 25

int main()
{
    int time, t1, count, lake, i, j, max, maxfish, loc, pos, roadtime, sum[lake_sum] = {0},
        ti[lake_sum], spendtime[lake_sum][lake_sum], fi[lake_sum], cpy[lake_sum], di[lake_sum];

    while(1)
    {

        scanf("%d", &lake);
        if(lake == 0)
            break;

        memset(spendtime, 0, lake_sum*lake_sum*sizeof(int));
        memset(sum, 0, lake_sum*sizeof(int));

        maxfish = 0;
        pos = 0;
        t1 = 0;

        scanf("%d", &time);
        time *= 12;

        for(i = 0; i < lake; i++)
        {
            scanf("%d", &fi[i]);
        }
        for(i = 0; i < lake; i++)
        {
            scanf("%d", &di[i]);
        }
        for(i = 0; i < lake - 1; i++)
        {
            scanf("%d", &ti[i]);
        }

        //Ã¶¾Ù
        for(i = 0; i < lake; i++)
        {
            count = 0;
            roadtime = 0;
            for(j = 0; j < i; j++)
            {
                roadtime += ti[j];
            }

            if(time <= roadtime)
                break;

            t1 = time - roadtime;
            memcpy(cpy, fi, lake_sum*sizeof(int));
            //µöÓã
            while(1)
            {
                loc = max = 0;

                for(j = 0; j <= i; j++)
                {
                    if(cpy[j] > max)
                    {
                        max = cpy[j];
                        loc = j;
                    }
                }
                if(cpy[loc] > di[loc])
                    cpy[loc] -= di[loc];
                else
                    cpy[loc] = 0;

                spendtime[i][loc]++;
                sum[i] += max;
//printf("%d\n",spendtime[i][loc]);
                if(++count == t1)
                    break;
            }

            if(sum[i] > maxfish)
            {
                maxfish = sum[i];
                pos = i;
            }
        }

        count = 0;

        for(i = 0; i < lake; i++)
        {
            if(sum[i] == maxfish)
                count++;
        }

            for(i = 0; i < lake - 1; i++)
                printf("%d, ",spendtime[pos][i] * 5);
            printf("%d\nNumber of fish expected: %d\n\n",spendtime[pos][lake-1] * 5, maxfish);
    }
    return 0;
}

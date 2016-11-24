#include <stdio.h>
#include <string.h>
int main()
{
    int i, j, n, in, stack[1000], out[1000];

    while(scanf("%d", &n), n)
    {

        while(scanf("%d", &out[0]), out[0])
        {

            for(i = 1; i < n; i++)
            {
                scanf("%d", &out[i]);
            }

            memset(stack, -1, sizeof(int));
            i = 0, j = 0, in = 1, stack[0] = 1;

            while(1)
            {
                if(out[i] == stack[j])
                {
                    if(0 == j && in == n)
                    {
                        printf("Yes\n");
                        break;
                    }
                    else if(0 == j)
                        i++, stack[j] = ++in;
                    else
                    {
                        i++, j--;
                    }
                }
                else
                {
                    if(in == n)
                    {
                        printf("No\n");
                        break;
                    }
                    stack[++j] = ++in;
                }
            }
        }
        printf("\n");
    }
    return 0;
}

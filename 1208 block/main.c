#include <stdio.h>
#include <string.h>
#define MAX 25

void re(int block[25][25], int x, int y, int n)
{
    block[x][y] = -1;
    block[n][0] = n;
}

int findx(int block[25][25], int n)
{
    int i, j;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            if(block[i][j] == n)
            {
                return i;
            }
        }
    }
    return 0;
}
int findy(int block[25][25], int n)
{
    int i, j;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            if(block[i][j] == n)
            {
                return j;
            }
        }
    }
    return 0;
}
void mt(int block[25][25], int from, int to)
{
    int x1, y1, x2, y2, i;
    x1 = findx(block, from);
    y1 = findy(block, from);
    x2 = findx(block, to);
    y2 = findy(block, to);

    for(i = y1+1; block[x1][i] != -1; i++)
    {
        re(block, x1, i, block[x1][i]);
    }
    for(i = y2+1; block[x2][i] != -1; i++)
    {
        re(block, x2, i, block[x2][i]);
    }
    block[x1][y1] = -1;
    block[x2][y2+1] = from;
}
void mo(int block[25][25], int from, int to)
{
    int x1, y1, x2, i;
    x1 = findx(block, from);
    y1 = findy(block, from);
    x2 = findx(block, to);

    for(i = y1+1; -1 != block[x1][i]; i++)
    {
        re(block, x1, i, block[x1][i]);
    }
    for(i = 1; i < MAX; i++)
    {
        if(-1 == block[x2][i])
        {
            block[x2][i] = from;
            block[x1][y1] = -1;
            break;
        }
    }
}
void pt(int block[25][25], int from, int to)
{
    int x1, y1, x2, y2, i;
    x1 = findx(block, from);
    y1 = findy(block, from);
    x2 = findx(block, to);
    y2 = findy(block, to);

    for(i = y2+1; -1 != block[x2][i]; i++)
    {
        re(block, x2, i, block[x2][i]);
    }

    for(i = y1; -1 != block[x1][i]; i++)
    {
        block[x2][++y2] = block[x1][i];
        block[x1][i] = -1;
    }
}
void po(int block[25][25], int from, int to)
{
    int x1, y1, x2, y2, i;
    x1 = findx(block, from);
    y1 = findy(block, from);
    x2 = findx(block, to);
    for(i = 1; i < MAX; i++)
    {
        if(-1 == block[x2][i])
        {
            y2 = i;
            break;
        }
    }
    for(i = y1; -1 != block[x1][i]; i++)
    {
        block[x2][y2++] = block[x1][i];
        block[x1][i] = -1;
    }
}

int main()
{
    int i, j, n, from, pos, to, x, block[25][25];
    char co[5];
    memset(block, -1, 25*25*sizeof(int));

    scanf("%d", &n);

    for(i = 0; i < n; i++)
        block[i][0] = i;

    while(scanf("%s", co), strcmp(co, "quit"))
    {
        scanf("%d", &from);

        if(!strcmp(co, "move"))
        {
            scanf("%s", co);
            scanf("%d", &to);
            x = findx(block, from);
            pos = findx(block, to);
            if(pos == x)
                continue;
            if(!strcmp(co, "onto"))
                mt(block, from, to);
            else
                mo(block, from, to);
        }
        else
        {
            scanf("%s", co);
            scanf("%d", &to);
            x = findx(block, from);
            pos = findx(block, to);
            if(pos == x)
                continue;
            if(!strcmp(co, "onto"))
                pt(block, from, to);
            else
                po(block, from, to);
        }
    }

    for(i = 0; i < n; i++)
    {
        printf("%d:", i);
        for(j = 0; j < n; j++)
            if(block[i][j] != -1)
                printf(" %d", block[i][j]);
        printf("\n");
    }
    printf("\n");
    return 0;
}

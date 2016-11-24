#include <stdio.h>
#define MAX 20

int search(char t[][20], int i, int j, int l, int w, int c)
{
    if(i >= 0 && i < l && j >=0 && j < w && t[i][j] == '.')
    {
        t[i][j] = '#';
        c++;
    }
    else
        return c;

    c = search(t, i-1, j, l, w, c);
    c = search(t, i, j-1, l, w, c);
    c = search(t, i+1, j, l, w, c);
    c = search(t, i, j+1, l, w, c);

    return c;
}

int main()
{
    char tile[MAX][MAX];
    int i, j, x, y, len, wid, count;

    while(1)
    {
        count = 0;

        scanf("\n%d%d", &wid, &len);

        if(len == 0)
            break;

        for(i = 0; i < len; i++)
        {
            getchar();
            for(j = 0; j < wid; j++)
            {
                scanf("%c", &tile[i][j]);
                if(tile[i][j] == '@')
                {
                    x = i;
                    y = j;
                    tile[i][j] = '.';
                }
            }
        }
        count = search(tile, x, y, len, wid, count);

        printf("%d\n", count);
    }
    return 0;
}

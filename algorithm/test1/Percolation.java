package test1;

import java.util.Scanner;

import edu.princeton.cs.algs4.Stopwatch;

/**
 * 渗透模型：我们使用N×N网格点来模型一个渗透系统。
 * 每个格点或是open格点或是blocked格点。
 * 一个full site是一个open格点，它可以通过一连
 * 串的邻近（左，右，上，下）open格点连通到顶行
 * 的一个open格点。如果在底行中有一个full site格点，则称系统是渗透的。
 * <p>
 * 功能实现：计算出每次模型渗透时，开启区域占总区域个数的百分比(即渗透率)。
 *
 * @author libx
 */
public class Percolation
{

    private int gridLength;//网格长度
    private int gridCount;//网格总数
    private boolean[] grid;//判断网格是否为开放，true：open false:block
    final static int T = 1000;//循环次数
    //private WeightedQuickUnionUF wqu;//包括网格顶部和低部
    private WeightedQuickCompressUF wqu;
    //private QuickFindUF wqu;
    //private QuickUnionUF wqu;
    public Percolation(int n)//初始化网格
    {
        gridLength = n;
        gridCount = n * n;
        grid = new boolean[gridCount];//初始化所有网格为block

        //wqu = new WeightedQuickUnionUF(gridCount + 2);
        wqu = new WeightedQuickCompressUF(gridCount + 2);
        //wqu = new QuickFindUF(gridCount + 2);
        //wqu = new QuickUnionUF(gridCount + 2);
    }

    public int position(int x, int y)//该网格所处的位置序号
    {
        return (x - 1) * gridLength + (y - 1);
    }

    public boolean isopen(int x, int y)//判断该网格是否开放
    {
        return grid[position(x, y)];
    }

    /*public boolean isfull(int x,int y)//判断该网格是否与顶部连通
    {
        return wqu2.connected(gridCount,position(x, y));
    }*/
    public boolean percolates()//判断该系统是否已经渗漏
    {
        return wqu.connected(gridCount, gridCount + 1);
    }

    public void open(int x, int y)//将该网格设置为opne并连接
    {
        int t = position(x, y);//该网格的序号
        if (isopen(x, y))//该网格已经开放
            return;
        grid[t] = true;//将其设为true
        if (x == 1)//该网格位于第一行,将此网格与顶部连接
        {
            wqu.union(gridCount, t);
            //wqu2.union(gridCount, t);
        }
        if (x == gridLength)//该网格位于最后一行，与底部连接
        {
            wqu.union(gridCount + 1, t);
        }
        if (x > 1)
        {
            int h = position(x - 1, y);
            if (grid[h])//判断该网格的下一行是否open
            {
                wqu.union(t, h);
                //wqu2.union(t, h);
            }
        }
        if (x < gridLength)
        {
            int h = position(x + 1, y);
            if (grid[h])
            {
                wqu.union(t, h);
                //wqu2.union(t, h);
            }
        }
        if (y > 1)
        {
            int h = position(x, y - 1);
            if (grid[h])
            {
                wqu.union(t, h);
                //wqu2.union(t, h);
            }
        }
        if (y < gridLength)
        {
            int h = position(x, y + 1);
            if (grid[h])
            {
                wqu.union(t, h);
                //wqu2.union(t, h);
            }
        }
    }
}

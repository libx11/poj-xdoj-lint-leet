package test1;

import java.util.Scanner;

import edu.princeton.cs.algs4.Stopwatch;

/**
 * ��͸ģ�ͣ�����ʹ��N��N�������ģ��һ����͸ϵͳ��
 * ÿ��������open������blocked��㡣
 * һ��full site��һ��open��㣬������ͨ��һ��
 * �����ڽ������ң��ϣ��£�open�����ͨ������
 * ��һ��open��㡣����ڵ�������һ��full site��㣬���ϵͳ����͸�ġ�
 * <p>
 * ����ʵ�֣������ÿ��ģ����͸ʱ����������ռ����������İٷֱ�(����͸��)��
 *
 * @author libx
 */
public class Percolation
{

    private int gridLength;//���񳤶�
    private int gridCount;//��������
    private boolean[] grid;//�ж������Ƿ�Ϊ���ţ�true��open false:block
    final static int T = 1000;//ѭ������
    //private WeightedQuickUnionUF wqu;//�������񶥲��͵Ͳ�
    private WeightedQuickCompressUF wqu;
    //private QuickFindUF wqu;
    //private QuickUnionUF wqu;
    public Percolation(int n)//��ʼ������
    {
        gridLength = n;
        gridCount = n * n;
        grid = new boolean[gridCount];//��ʼ����������Ϊblock

        //wqu = new WeightedQuickUnionUF(gridCount + 2);
        wqu = new WeightedQuickCompressUF(gridCount + 2);
        //wqu = new QuickFindUF(gridCount + 2);
        //wqu = new QuickUnionUF(gridCount + 2);
    }

    public int position(int x, int y)//������������λ�����
    {
        return (x - 1) * gridLength + (y - 1);
    }

    public boolean isopen(int x, int y)//�жϸ������Ƿ񿪷�
    {
        return grid[position(x, y)];
    }

    /*public boolean isfull(int x,int y)//�жϸ������Ƿ��붥����ͨ
    {
        return wqu2.connected(gridCount,position(x, y));
    }*/
    public boolean percolates()//�жϸ�ϵͳ�Ƿ��Ѿ���©
    {
        return wqu.connected(gridCount, gridCount + 1);
    }

    public void open(int x, int y)//������������Ϊopne������
    {
        int t = position(x, y);//����������
        if (isopen(x, y))//�������Ѿ�����
            return;
        grid[t] = true;//������Ϊtrue
        if (x == 1)//������λ�ڵ�һ��,���������붥������
        {
            wqu.union(gridCount, t);
            //wqu2.union(gridCount, t);
        }
        if (x == gridLength)//������λ�����һ�У���ײ�����
        {
            wqu.union(gridCount + 1, t);
        }
        if (x > 1)
        {
            int h = position(x - 1, y);
            if (grid[h])//�жϸ��������һ���Ƿ�open
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

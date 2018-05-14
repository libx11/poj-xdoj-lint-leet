package test1;

/**
 * 功能:快速合并算法
 *
 * @author libx
 */
public class QuickUnionUF
{

    private int[] id;
    private int count;

    public QuickUnionUF(int n)
    {
        count = n;
        id = new int[n];
        for (int i = 0; i < n; i++)
            id[i] = i;
    }

    //查找连通分量数量
    public int count()
    {
        return count;
    }

    //查找点的根结点
    public int root(int p)
    {
        while (p != id[p])
            p = id[p];
        return p;
    }

    //检验两个点是否连通
    public boolean connected(int p, int q)
    {
        return root(p) == root(q);
    }

    //合并两个点
    public void union(int p, int q)
    {
        int pRoot = root(p);
        int qRoot = root(q);
        if (pRoot == qRoot)//两个点已经连通
            return;
        id[pRoot] = qRoot;
        count--;
    }
}

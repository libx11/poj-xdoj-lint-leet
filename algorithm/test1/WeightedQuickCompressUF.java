package test1;

/**
 * 功能：带路径压缩的带权快速合并(接近于线性)
 *
 * @author libx
 */
public class WeightedQuickCompressUF
{

    private int[] id;
    private int[] size;
    private int count;

    public WeightedQuickCompressUF(int n)
    {
        count = n;
        id = new int[n];
        size = new int[n];//权值
        for (int i = 0; i < n; i++)
        {
            id[i] = i;
            size[i] = i;
        }
    }

    public int count()
    {
        return count;
    }

    public int find(int p)
    {
        while (p != id[p])
        {
            id[p] = id[id[p]];//路径压缩
            p = id[p];
        }
        return p;
    }

    public boolean connected(int p, int q)
    {
        return find(p) == find(q);
    }

    public void union(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot)
            return;
        if (size[pRoot] < size[qRoot])
        {
            id[pRoot] = qRoot;
            size[qRoot] += size[pRoot];
        }
        else
        {
            id[qRoot] = pRoot;
            size[pRoot] += size[qRoot];
        }
    }
}

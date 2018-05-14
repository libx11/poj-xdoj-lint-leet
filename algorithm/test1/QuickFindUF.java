package test1;

/**
 * 功能：快速查找合并算法
 *
 * @author libx
 */
public class QuickFindUF
{

    private int[] id;//点的下标
    private int count;//连通分量数量

    public QuickFindUF(int n)
    {
        count = n;
        id = new int[n];
        for (int i = 0; i < n; i++)//初始化点的位置
            id[i] = i;
    }

    //查找连通分量数量
    public int count()
    {
        return count;
    }

    //查找点的id
    public int find(int p)
    {
        return id[p];
    }

    //检验两个点是否连通
    public boolean connected(int p, int q)
    {
        return find(p) == find(q);
    }

    //合并两个点
    public void union(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);
        if (pId == qId)//两个点已经连通
            return;
        for (int i = 0; i < id.length; i++)
        {
            if (id[i] == pId)
                id[i] = qId;
        }
    }
}

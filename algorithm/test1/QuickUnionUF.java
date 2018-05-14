package test1;

/**
 * ����:���ٺϲ��㷨
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

    //������ͨ��������
    public int count()
    {
        return count;
    }

    //���ҵ�ĸ����
    public int root(int p)
    {
        while (p != id[p])
            p = id[p];
        return p;
    }

    //�����������Ƿ���ͨ
    public boolean connected(int p, int q)
    {
        return root(p) == root(q);
    }

    //�ϲ�������
    public void union(int p, int q)
    {
        int pRoot = root(p);
        int qRoot = root(q);
        if (pRoot == qRoot)//�������Ѿ���ͨ
            return;
        id[pRoot] = qRoot;
        count--;
    }
}

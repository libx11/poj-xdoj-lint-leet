package test1;

/**
 * ���ܣ����ٲ��Һϲ��㷨
 *
 * @author libx
 */
public class QuickFindUF
{

    private int[] id;//����±�
    private int count;//��ͨ��������

    public QuickFindUF(int n)
    {
        count = n;
        id = new int[n];
        for (int i = 0; i < n; i++)//��ʼ�����λ��
            id[i] = i;
    }

    //������ͨ��������
    public int count()
    {
        return count;
    }

    //���ҵ��id
    public int find(int p)
    {
        return id[p];
    }

    //�����������Ƿ���ͨ
    public boolean connected(int p, int q)
    {
        return find(p) == find(q);
    }

    //�ϲ�������
    public void union(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);
        if (pId == qId)//�������Ѿ���ͨ
            return;
        for (int i = 0; i < id.length; i++)
        {
            if (id[i] == pId)
                id[i] = qId;
        }
    }
}

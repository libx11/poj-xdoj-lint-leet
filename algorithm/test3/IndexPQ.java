package test3;

/**
 * ���ܣ�����һ���������ȶ���
 *
 * @author libx
 */
public class IndexPQ
{
    private int N;//������Ԫ������
    private int[] pq;//Ԫ�صļ�ֵ
    private int[] qp;//����ֵ
    private double[] priority;//Ԫ������

    public IndexPQ(int NMAX)
    {
        pq = new int[NMAX + 1];
        qp = new int[NMAX + 1];
        priority = new double[NMAX + 1];
        N = 0;
    }

    //�ж϶����Ƿ�Ϊ��
    public boolean isEmpty()
    {
        return N == 0;
    }

    //������в���Ԫ��
    public void put(int k, double value)
    {
        N++;
        qp[k] = N;//�������ֵ�����
        pq[N] = k;//���Ԫ�صļ�ֵ
        priority[k] = value;//���Ԫ�ص�����
        swim(pq, N);
    }

    //ɾ�������м�ֵ��С��Ԫ��
    public int delMin()
    {
        exch(pq[1], pq[N]);
        sink(pq, 1, --N);
        return pq[N + 1];
    }

    //�����ֵ���ڣ���ı�����
    public void change(int k, double value)
    {
        priority[k] = value;
        swim(pq, qp[k]);
        sink(pq, qp[k], N);
    }

    //�Ƚ�Ԫ��i�Ƿ��j��
    private boolean greater(int i, int j)
    {
        return priority[i] > priority[j];
    }

    //����Ԫ��
    private void exch(int i, int j)
    {
        int t = qp[i];
        qp[i] = qp[j];
        qp[j] = t;
        pq[qp[i]] = i;
        pq[qp[j]] = j;

    }

    //Ԫ���ϸ�
    private void swim(int[] a, int k)
    {
        while (k > 1 && greater(a[k / 2], a[k]))
        {
            exch(a[k], a[k / 2]);
            k = k / 2;
        }
    }

    //Ԫ���³�
    private void sink(int[] a, int k, int N)
    {
        int j;
        while (2 * k <= N)
        {
            j = 2 * k;
            if (j < N && greater(a[j], a[j + 1]))
                j++;
            if (!greater(a[k], a[j]))
                break;
            exch(a[k], a[j]);
            k = j;
        }
    }

}

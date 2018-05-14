package test3;

/**
 * 功能：创建一个索引优先队列
 *
 * @author libx
 */
public class IndexPQ
{
    private int N;//队列中元素数量
    private int[] pq;//元素的键值
    private int[] qp;//索引值
    private double[] priority;//元素内容

    public IndexPQ(int NMAX)
    {
        pq = new int[NMAX + 1];
        qp = new int[NMAX + 1];
        priority = new double[NMAX + 1];
        N = 0;
    }

    //判断队列是否为空
    public boolean isEmpty()
    {
        return N == 0;
    }

    //向队列中插入元素
    public void put(int k, double value)
    {
        N++;
        qp[k] = N;//存放索引值的序号
        pq[N] = k;//存放元素的键值
        priority[k] = value;//存放元素的内容
        swim(pq, N);
    }

    //删除队列中键值最小的元素
    public int delMin()
    {
        exch(pq[1], pq[N]);
        sink(pq, 1, --N);
        return pq[N + 1];
    }

    //如果键值存在，则改变内容
    public void change(int k, double value)
    {
        priority[k] = value;
        swim(pq, qp[k]);
        sink(pq, qp[k], N);
    }

    //比较元素i是否比j大
    private boolean greater(int i, int j)
    {
        return priority[i] > priority[j];
    }

    //交换元素
    private void exch(int i, int j)
    {
        int t = qp[i];
        qp[i] = qp[j];
        qp[j] = t;
        pq[qp[i]] = i;
        pq[qp[j]] = j;

    }

    //元素上浮
    private void swim(int[] a, int k)
    {
        while (k > 1 && greater(a[k / 2], a[k]))
        {
            exch(a[k], a[k / 2]);
            k = k / 2;
        }
    }

    //元素下沉
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

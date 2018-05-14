package test2;

/**
 * ���ܣ�ʵ�ֿ�������
 *
 * @author libx
 */
public class Quick
{

    public static void sort(Comparable[] a)
    {
        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi)
    {
        if (hi <= lo)
            return;
        int j = partition(a, lo, hi);//�����з�
        sort(a, lo, j - 1);//�������
        sort(a, j + 1, hi);//�ұ�����

    }

    private static int partition(Comparable[] a, int lo, int hi)//����������з�
    {
        int i = lo, j = hi + 1;
        Comparable v = a[lo];//�з�Ԫ��
        while (true)//����ɨ�裬���ɨ���Ƿ����������Ԫ��
        {
            while (less(a[++i], v))
                if (i == hi)
                    break;
            while (less(v, a[--j]))
                if (j == lo)
                    break;
            if (i >= j)
                break;
            exch(a, i, j);
        }
        exch(a, lo, j);//��v������ȷ��λ��
        return j;
    }

    private static boolean less(Comparable i, Comparable j)//�ж�����ֵ�Ĵ�С,��iС��j�����Ϊ��
    {
        return i.compareTo(j) < 0;
    }

    private static void exch(Comparable[] a, int i, int j)//����a[i]��a[j]
    {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

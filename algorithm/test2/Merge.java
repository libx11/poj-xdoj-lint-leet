package test2;

/**
 * 功能：实现归并排序
 *
 * @author libx
 */

public class Merge
{

    private static Comparable[] aux;//辅助数组

    //自顶向下的归并排序
    public static void ToptoBottom_sort(Comparable[] a)
    {
        aux = new Comparable[a.length];

        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi)
    {
        if (hi <= lo)
            return;
        int mid = (lo + hi) / 2;
        sort(a, lo, mid);//将左边排序
        sort(a, mid + 1, hi);//将右边排序
        if (!less(a[mid + 1], a[mid]))
            return;
        merge(a, lo, mid, hi);
    }

    //自底向上的归并排序
    public static void BottomtoTop_sort(Comparable[] a)
    {
        int N = a.length;
        aux = new Comparable[N];
        for (int sz = 1; sz < N; sz += sz)
        {
            for (int lo = 0; lo < N - sz; lo += sz + sz)
                merge(a, lo, lo + sz - 1, Math.min(lo + sz + sz - 1, N - 1));
        }
    }

    private static void merge(Comparable[] a, int lo, int mid, int hi)
    {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++)
            aux[k] = a[k];
        for (int k = lo; k <= hi; k++)
        {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > hi)
                a[k] = aux[i++];
            else if (less(aux[j], aux[i]))
                a[k] = aux[j++];
            else
                a[k] = aux[i++];
        }
    }

    private static boolean less(Comparable i, Comparable j)//判断两个值的大小,若i小于j则输出为真
    {
        return i.compareTo(j) < 0;
    }
}

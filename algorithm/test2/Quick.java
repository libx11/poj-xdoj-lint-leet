package test2;

/**
 * 功能：实现快速排序
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
        int j = partition(a, lo, hi);//进行切分
        sort(a, lo, j - 1);//左边排序
        sort(a, j + 1, hi);//右边排序

    }

    private static int partition(Comparable[] a, int lo, int hi)//将数组进行切分
    {
        int i = lo, j = hi + 1;
        Comparable v = a[lo];//切分元素
        while (true)//左右扫描，检查扫描是否结束并交换元素
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
        exch(a, lo, j);//将v放入正确的位置
        return j;
    }

    private static boolean less(Comparable i, Comparable j)//判断两个值的大小,若i小于j则输出为真
    {
        return i.compareTo(j) < 0;
    }

    private static void exch(Comparable[] a, int i, int j)//交换a[i]与a[j]
    {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

package test2;

import java.util.Scanner;

import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch;

/**
 * �Ƚϸ��������㷨
 *
 * @author libx
 */
public class Example implements Comparable<Integer>
{

    public static void main(String[] args)
    {
        // TODO �Զ����ɵķ������
        double T = 0, M = 0;

        Scanner reader = new Scanner(System.in);
        System.out.println("Please input N:");
        int N = reader.nextInt();

        Comparable[] a = new Comparable[N];
        Comparable[] b = new Comparable[N];
        for (int i = 0; i < N; i++)//���������
        {
            int t = (int) (Math.random() * (N)) + 1;

            b[i] = t;
        }
        for (int k = 0; k < 10; k++)
        {
            for (int i = 0; i < N; i++)
            {
                a[i] = b[i];
            }
            Stopwatch s = new Stopwatch();
            Runtime rt = Runtime.getRuntime();
            rt.gc();//������������
            long m1 = (rt.totalMemory() - rt.freeMemory());//δ����ǰռ���ڴ�
            //insertSort(a);
            //Merge.ToptoBottom_sort(a);
            //Merge.BottomtoTop_sort(a);
            //Quick.sort(a);
            Quick3way.sort(a);
            long m2 = (rt.totalMemory() - rt.freeMemory());//�����ռ���ڴ�
            double t1 = s.elapsedTime();
            //System.out.println("Run1:"+t1);
            T += t1;
            M += Math.abs(m2 - m1);
            System.out.printf("Run%d:%.3fs\n", k + 1, t1);
            //System.out.println("Time:Run"+(k+1)+":"+t1+"s");
            //System.out.println("Memory:Run"+(k+1)+":"+Math.abs(m1-m2)/1024+"KB");

        }
        System.out.printf("��������ƽ��ʱ�䣺%.3fs\n", T / 10);
        //System.out.println("������ռƽ���ڴ棺"+M/10/1024+"KB");
        assert isSorted(a);
    }

    //ѡ������
    public static void selectSort(Comparable[] a)
    {
        int N = a.length;
        for (int i = 0; i < N; i++)
        {
            int min = i;
            for (int j = i + 1; j < N; j++)
                if (less(a[j], a[min]))
                    min = j;
            exch(a, i, min);
        }
    }

    //��������
    public static void insertSort(Comparable[] a)
    {
        int N = a.length;
        for (int i = 1; i < N; i++)
        {
            Comparable t = a[i];
            int j;
            for (j = i; j > 0 && less(t, a[j - 1]); j--)
                a[j] = a[j - 1];
            a[j] = t;
        }
    }

    //ϣ������
    public static void shellSort(Comparable[] a)
    {
        int N = a.length;
        int h = 1;
        while (h < N / 3)
            h = h * 3 + 1;
        while (h >= 1)
        {
            for (int i = h; i < N; i++)
            {
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
                    exch(a, j, j - h);
            }
            h = h / 3;
        }
    }

    private static void exch(Comparable[] a, int i, int j)//����a[i]��a[j]
    {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    private static void show(Comparable[] a)//�������
    {
        for (int i = 0; i < a.length; i++)
            System.out.println(a[i]);
    }

    private static boolean less(Comparable i, Comparable j)//�ж�����ֵ�Ĵ�С,��iС��j�����Ϊ��
    {
        return i.compareTo(j) < 0;
    }

    private static boolean isSorted(Comparable[] a)//�жϸ������Ƿ��Ѿ�����
    {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i - 1]))
                return false;
        return true;
    }

    @Override
    public int compareTo(Integer o)
    {
        // TODO �Զ����ɵķ������
        return 0;
    }

}

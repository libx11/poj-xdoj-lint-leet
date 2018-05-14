package test1;

import java.util.Scanner;

import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.StopwatchCPU;

/**
 * ���ܣ�������͸ϵͳ�ķ���ֵ
 *
 * @author libx
 */
public class PercolationStats
{
    private static int N;//���񳤶�
    private static int T;//���д���
    private static double[] a;//��T��ʵ���������ʽ��б���
    private static double mean = 0;//ƽ��ֵ
    private static double stddev = 0;//��׼��
    private static double v = 0;
    private static double confidenceLow;//����������
    private static double confidenceHigh;//����������

    public static void main(String[] args)
    {
        Scanner reader = new Scanner(System.in);
        System.out.print("Please input N,T:");
        while (reader.hasNext())
        {
            N = reader.nextInt();
            T = reader.nextInt();
            a = new double[T];
            new PercolationStats(N, T);
            System.out.println("Example values after creating PercolationStats(" + N + "," + T + ")");
            mean = mean();//ƽ��ֵ
            System.out.println("mean()= " + mean);
            stddev = stddev();//��׼��
            System.out.println("stddev()= " + stddev());
            v = 1.96 * stddev / Math.sqrt(T);
            confidenceLow = confidenceLo();//����������
            System.out.println("confidenceLow()= " + confidenceLow);
            confidenceHigh = confidenceHi();//��������������
            System.out.println("confidenceHigh()= " + confidenceHigh);
            System.out.print("Please input N,T:");
        }
    }

    public PercolationStats(int N, int T)//����N����������͸ϵͳ��ʱ�����
    {
        this.N = N;
        this.T = T;
        Stopwatch s = new Stopwatch();//��ʼ��ʱ
        long m1 = Runtime.getRuntime().freeMemory() / 1024;//����ǰռ�������ڴ�
        for (int i = 0; i < T; i++)
        {
            Percolation p = new Percolation(N);
            int count = 0;//���Ÿ�����
            while (true)
            {
                int x = (int) (Math.random() * N) + 1;
                int y = (int) (Math.random() * N) + 1;
                if (!p.isopen(x, y))
                    count++;
                p.open(x, y);
                if (p.percolates())
                {
                    //System.out.println("����͸,���Ÿ�����Ϊ��"+count+" ��͸��Ϊ��"+(double)(count)/(n*n));
                    a[i] = (double) (count) / (N * N);
                    break;
                }
            }
        }
        double time = s.elapsedTime();
        long m2 = Runtime.getRuntime().freeMemory() / 1024;//���к�ռ�������ڴ�
        System.out.println("����" + T + "�λ���ʱ�䣺" + time + "s");
        System.out.println("����" + T + "��ʱռ���ڴ棺" + (m1 - m2) + "KB");
    }

    public static double mean()//������͸�ʵľ�ֵ
    {
        double sum = 0;
        for (int i = 0; i < T; i++)
            sum += a[i];
        mean = sum / T;
        return mean;
    }

    public static double stddev()//������͸�ʵı�׼��
    {
        double sumAdd = 0;
        for (int i = 0; i < T; i++)
            sumAdd += Math.pow((a[i] - mean), 2);
        double stddev = Math.sqrt(sumAdd / T);
        return stddev;
    }

    public static double confidenceLo()//����������
    {
        double confidenceLow = mean - v;
        return confidenceLow;
    }

    public static double confidenceHi()//����������
    {
        double confidenceHigh = mean + v;
        return confidenceHigh;
    }
}

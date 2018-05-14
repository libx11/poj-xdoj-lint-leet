package test1;

import java.util.Scanner;

import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.StopwatchCPU;

/**
 * 功能：计算渗透系统的分析值
 *
 * @author libx
 */
public class PercolationStats
{
    private static int N;//方格长度
    private static int T;//运行次数
    private static double[] a;//对T此实验后的渗滤率进行保存
    private static double mean = 0;//平均值
    private static double stddev = 0;//标准差
    private static double v = 0;
    private static double confidenceLow;//置信下区间
    private static double confidenceHigh;//置信上区间

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
            mean = mean();//平均值
            System.out.println("mean()= " + mean);
            stddev = stddev();//标准差
            System.out.println("stddev()= " + stddev());
            v = 1.96 * stddev / Math.sqrt(T);
            confidenceLow = confidenceLo();//置信下区间
            System.out.println("confidenceLow()= " + confidenceLow);
            confidenceHigh = confidenceHi();//置信上区间区间
            System.out.println("confidenceHigh()= " + confidenceHigh);
            System.out.print("Please input N,T:");
        }
    }

    public PercolationStats(int N, int T)//计算N次试验下渗透系统的时间分析
    {
        this.N = N;
        this.T = T;
        Stopwatch s = new Stopwatch();//开始计时
        long m1 = Runtime.getRuntime().freeMemory() / 1024;//运行前占用自由内存
        for (int i = 0; i < T; i++)
        {
            Percolation p = new Percolation(N);
            int count = 0;//开放格子数
            while (true)
            {
                int x = (int) (Math.random() * N) + 1;
                int y = (int) (Math.random() * N) + 1;
                if (!p.isopen(x, y))
                    count++;
                p.open(x, y);
                if (p.percolates())
                {
                    //System.out.println("已渗透,开放格子数为："+count+" 渗透率为："+(double)(count)/(n*n));
                    a[i] = (double) (count) / (N * N);
                    break;
                }
            }
        }
        double time = s.elapsedTime();
        long m2 = Runtime.getRuntime().freeMemory() / 1024;//运行后占用自由内存
        System.out.println("运行" + T + "次花费时间：" + time + "s");
        System.out.println("运行" + T + "次时占用内存：" + (m1 - m2) + "KB");
    }

    public static double mean()//计算渗透率的均值
    {
        double sum = 0;
        for (int i = 0; i < T; i++)
            sum += a[i];
        mean = sum / T;
        return mean;
    }

    public static double stddev()//计算渗透率的标准差
    {
        double sumAdd = 0;
        for (int i = 0; i < T; i++)
            sumAdd += Math.pow((a[i] - mean), 2);
        double stddev = Math.sqrt(sumAdd / T);
        return stddev;
    }

    public static double confidenceLo()//置信下区间
    {
        double confidenceLow = mean - v;
        return confidenceLow;
    }

    public static double confidenceHi()//置信上区间
    {
        double confidenceHigh = mean + v;
        return confidenceHigh;
    }
}

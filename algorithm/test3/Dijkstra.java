package test3;

import java.awt.BasicStroke;
import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import edu.princeton.cs.algs4.Stopwatch;

/**
 * 功能：迪杰斯特拉算法求最短路径
 *
 * @author libx
 */
public class Dijkstra extends JFrame
{

    private static double INFINITY = Double.MAX_VALUE;
    private static double EPSILON = 0.000001;

    private EuclideanGraph G;
    private double[] distTo;//从起点都某点的最短路径
    private int[] pred;//测试某点的上一点是哪个，若没有则设置为-1
    private IndexPQ pq;//索引优先队列

    private JTextArea jta = null;
    private JScrollPane jsp = null;

    //构造方法初始化
    public Dijkstra(EuclideanGraph G)
    {
        this.G = G;
        jta = new JTextArea();
        jsp = new JScrollPane(jta);
        this.add(jsp);
        this.setTitle("路径显示区");
        this.setSize(500, 500);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    private void dijkstra(int s, int d)
    {
        int V = G.V();
        distTo = new double[V];
        pred = new int[V];
        pq = new IndexPQ(V);
        for (int v = 0; v < V; v++)
        {
            distTo[v] = INFINITY;
            pred[v] = -1;
            pq.put(v, distTo[v]);
        }
        //设置起点的距离
        distTo[s] = 0.0;
        pred[s] = s;
        pq.change(s, distTo[s]);
        //改进1：一旦发现目的地的最短路径就停止搜索
        while (!pq.isEmpty())
        {
            int v = pq.delMin();
            if (pred[v] == -1)//该路径不可达
            {
                //JOptionPane.showMessageDialog(this, "There's not a path from s to d");
                break;
            }

            if (v == d)//已找到目的地
                break;
            relax(v);
        }
    }

    //放松顶点并确认下一个被放松的顶点
    private void relax(int v)
    {
        IntIterator i = G.neighbors(v);
        while (i.hasNext())
        {
            int w = i.next();//下一个点
            //更新数据
            if (distTo[w] - EPSILON > distTo[v] + G.distance(v, w))
            {
                distTo[w] = distTo[v] + G.distance(v, w);
                pq.change(w, distTo[w]);//将更新后的数据放入优先队列中
                pred[w] = v;//w点的上一个点为v
            }

        }
    }

    public String distance(int s, int d)
    {
        dijkstra(s, d);
        return String.format("%.5f", distTo[d]).toString();
    }

    //返回测试10次后的运行时间
    public String time(int s, int d)
    {
        double TotalTime = 0.0;
        for (int i = 0; i < 10; i++)
        {
            Stopwatch time = new Stopwatch();
            dijkstra(s, d);
            TotalTime += time.elapsedTime();
        }
        return String.format("%.5f", TotalTime / 10).toString();
    }

    //画出最短路径
    public void drawPath(int s, int d)
    {
        dijkstra(s, d);
        if (pred[d] == -1)
            return;
        Turtle.setColor(Color.red);
        for (int v = d; v != s; v = pred[v])
            G.point(v).drawTo(G.point(pred[v]));
        Turtle.render();
    }

    //显示最短路径及运行时间
    public void showPath(int d, int s)
    {
        jta.setText(null);
        jta.append("********From " + d + " to " + s + "********\n");
        dijkstra(s, d);
        if (pred[d] == -1)
        {
            String str = d + " is unreachable from " + s;
            jta.append(str);
            return;
        }
        int t = 0;
        for (int v = d; v != s; v = pred[v])
        {
            String str = v + "-";
            jta.append(str);
            t++;
            if (t % 20 == 0)
            {
                jta.append("\n");
            }
        }
        jta.append(Integer.toString(s) + "\n");
        String str = "最短路径长度：" + distance(s, d) + "\n";
        jta.append(str);
        String str1 = "寻找最短路径花费平均时间(测试10次)：" + time(s, d) + "s\n";
        jta.append(str1);
    }
}

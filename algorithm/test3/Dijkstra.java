package test3;

import java.awt.BasicStroke;
import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import edu.princeton.cs.algs4.Stopwatch;

/**
 * ���ܣ��Ͻ�˹�����㷨�����·��
 *
 * @author libx
 */
public class Dijkstra extends JFrame
{

    private static double INFINITY = Double.MAX_VALUE;
    private static double EPSILON = 0.000001;

    private EuclideanGraph G;
    private double[] distTo;//����㶼ĳ������·��
    private int[] pred;//����ĳ�����һ�����ĸ�����û��������Ϊ-1
    private IndexPQ pq;//�������ȶ���

    private JTextArea jta = null;
    private JScrollPane jsp = null;

    //���췽����ʼ��
    public Dijkstra(EuclideanGraph G)
    {
        this.G = G;
        jta = new JTextArea();
        jsp = new JScrollPane(jta);
        this.add(jsp);
        this.setTitle("·����ʾ��");
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
        //�������ľ���
        distTo[s] = 0.0;
        pred[s] = s;
        pq.change(s, distTo[s]);
        //�Ľ�1��һ������Ŀ�ĵص����·����ֹͣ����
        while (!pq.isEmpty())
        {
            int v = pq.delMin();
            if (pred[v] == -1)//��·�����ɴ�
            {
                //JOptionPane.showMessageDialog(this, "There's not a path from s to d");
                break;
            }

            if (v == d)//���ҵ�Ŀ�ĵ�
                break;
            relax(v);
        }
    }

    //���ɶ��㲢ȷ����һ�������ɵĶ���
    private void relax(int v)
    {
        IntIterator i = G.neighbors(v);
        while (i.hasNext())
        {
            int w = i.next();//��һ����
            //��������
            if (distTo[w] - EPSILON > distTo[v] + G.distance(v, w))
            {
                distTo[w] = distTo[v] + G.distance(v, w);
                pq.change(w, distTo[w]);//�����º�����ݷ������ȶ�����
                pred[w] = v;//w�����һ����Ϊv
            }

        }
    }

    public String distance(int s, int d)
    {
        dijkstra(s, d);
        return String.format("%.5f", distTo[d]).toString();
    }

    //���ز���10�κ������ʱ��
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

    //�������·��
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

    //��ʾ���·��������ʱ��
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
        String str = "���·�����ȣ�" + distance(s, d) + "\n";
        jta.append(str);
        String str1 = "Ѱ�����·������ƽ��ʱ��(����10��)��" + time(s, d) + "s\n";
        jta.append(str1);
    }
}

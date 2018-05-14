package test3;

import java.awt.BasicStroke;

import edu.princeton.cs.algs4.In;

/**
 * ���ܣ���������ͼ
 *
 * @author libx
 */
public class EuclideanGraph
{
    private final static String NEWLINE = System.getProperty("line.separator");
    private int V;//�����Ŀ
    private int E;//�ߵ� ��Ŀ
    private Node[] adj;//�ڽ�����
    private Point[] points;//����ͼ�ĵ�����

    //�����ڽ�����
    private static class Node
    {
        int v;
        Node next;

        Node(int v, Node next)
        {
            this.v = v;
            this.next = next;
        }
    }

    //�ڽ�����ĵ�����
    private class AdjListIterator implements IntIterator
    {
        private Node x;

        public AdjListIterator(Node x)
        {
            this.x = x;
        }

        //����Ƿ������ӵĵ�
        public boolean hasNext()
        {
            return x != null;
        }

        public int next()
        {
            int v = x.v;
            x = x.next;
            return v;
        }
    }

    //���ļ��ж�ȡ����ͼ����
    public EuclideanGraph(In in)
    {
        V = Integer.parseInt(in.readString());
        E = Integer.parseInt(in.readString());

        points = new Point[V];
        //��ȡ�������
        for (int i = 0; i < V; i++)
        {
            int v = Integer.parseInt(in.readString());
            int x = Integer.parseInt(in.readString());
            int y = Integer.parseInt(in.readString());
            if (v < 0 || v >= V)//�׳��쳣
            {
                throw new RuntimeException("Illegal vertex number");
            }
            //System.out.println(v+" "+x+" "+y);
            points[v] = new Point(x, y);//��¼��Щ��
        }
        //��ȡ��¼���
        adj = new Node[V];
        for (int i = 0; i < E; i++)
        {
            int v = Integer.parseInt(in.readString());
            int w = Integer.parseInt(in.readString());
            if (v < 0 || v >= V)
                throw new RuntimeException("Illegal vertex number");
            if (w < 0 || w >= V)
                throw new RuntimeException("Illegal vertex number");
            adj[v] = new Node(w, adj[v]);
            adj[w] = new Node(v, adj[w]);
        }
    }

    //���ر����͵���
    public int V()
    {
        return V;
    }

    public int E()
    {
        return E;
    }

    //����ĳ����ĺ�������
    public Point point(int i)
    {
        return points[i];
    }

    //����������֮��ľ���
    public double distance(int v, int w)
    {
        return points[v].distanceTo(points[w]);
    }

    //����v�ĵ�����
    public IntIterator neighbors(int v)
    {
        return new AdjListIterator(adj[v]);
    }

    public String toString()
    {
        String s = "";
        s += "V = " + V + NEWLINE;
        s += "E = " + E + NEWLINE;
        for (int v = 0; v < V && v < 100; v++)
        {
            String t = v + " " + points[v] + ": ";
            for (Node x = adj[v]; x != null; x = x.next)
                t += x.v + " ";
            s += t + NEWLINE;
        }
        return s;
    }

    //����ͼ�еĵ����
    public void draw()
    {
        for (int v = 0; v < V; v++)
        {
            points[v].draw();
            for (Node x = adj[v]; x != null; x = x.next)
            {
                int w = x.v;
                points[v].drawTo(points[w]);
            }
        }
        Turtle.render();
    }

    //���в���
    public static void main(String[] args)
    {
        In in = new In("E:/����/algorithm/usa.txt");
        EuclideanGraph G = new EuclideanGraph(in);
        System.out.println(G);
        Turtle.create(1000, 500);
        G.draw();
    }
}

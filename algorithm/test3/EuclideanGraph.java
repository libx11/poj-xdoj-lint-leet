package test3;

import java.awt.BasicStroke;

import edu.princeton.cs.algs4.In;

/**
 * 功能：构建无向图
 *
 * @author libx
 */
public class EuclideanGraph
{
    private final static String NEWLINE = System.getProperty("line.separator");
    private int V;//点的数目
    private int E;//边的 数目
    private Node[] adj;//邻接链表
    private Point[] points;//无向图的点坐标

    //构建邻接链表
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

    //邻接链表的迭代器
    private class AdjListIterator implements IntIterator
    {
        private Node x;

        public AdjListIterator(Node x)
        {
            this.x = x;
        }

        //检测是否还有连接的点
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

    //从文件中读取无向图数据
    public EuclideanGraph(In in)
    {
        V = Integer.parseInt(in.readString());
        E = Integer.parseInt(in.readString());

        points = new Point[V];
        //读取并插入点
        for (int i = 0; i < V; i++)
        {
            int v = Integer.parseInt(in.readString());
            int x = Integer.parseInt(in.readString());
            int y = Integer.parseInt(in.readString());
            if (v < 0 || v >= V)//抛出异常
            {
                throw new RuntimeException("Illegal vertex number");
            }
            //System.out.println(v+" "+x+" "+y);
            points[v] = new Point(x, y);//记录这些点
        }
        //读取并录入边
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

    //返回边数和点数
    public int V()
    {
        return V;
    }

    public int E()
    {
        return E;
    }

    //返回某个点的横纵坐标
    public Point point(int i)
    {
        return points[i];
    }

    //返回两个点之间的距离
    public double distance(int v, int w)
    {
        return points[v].distanceTo(points[w]);
    }

    //返回v的迭代器
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

    //画出图中的点与边
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

    //进行测试
    public static void main(String[] args)
    {
        In in = new In("E:/程序/algorithm/usa.txt");
        EuclideanGraph G = new EuclideanGraph(in);
        System.out.println(G);
        Turtle.create(1000, 500);
        G.draw();
    }
}

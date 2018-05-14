package test3;

import edu.princeton.cs.algs4.StdOut;

/**
 * 功能：记录每个点的坐标
 *
 * @author libx
 */
public class Point
{

    private final static double SCALEX = 0.0001 * 1000.0;
    private final static double SCALEY = 0.0001 * 1000.0 * 1.3;

    private int x;//点的横坐标
    private int y;//点的纵坐标

    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    //返回点的坐标值
    public String toString()
    {
        return "(" + x + ", " + y + ")";
    }

    //改造2：计算并返回两点之间的距离(欧氏距离求两点间实际距离)
    public double distanceTo(Point that)
    {
        double dx = this.x - that.x;
        double dy = this.y - that.y;
        double distance = Math.sqrt(dx * dx + dy * dy);
        return distance;
    }

    //画出点的位置
    public void draw()
    {
        Turtle.fly(x * SCALEX, y * SCALEY);
        Turtle.spot(2);
    }

    //画一条线连接该点与另一点
    public void drawTo(Point q)
    {
        Point p = this;
        Turtle.fly(p.x * SCALEX, p.y * SCALEY);
        Turtle.go(q.x * SCALEX, q.y * SCALEY);
    }
	/*public static void main(String[] args) {
		Point p=new Point(150, 200);
		Point q=new Point(150,500);
		Turtle.create(300, 200);
		p.draw();
		p.drawTo(q);
	}*/
}

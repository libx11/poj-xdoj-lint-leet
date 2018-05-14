package test3;

import edu.princeton.cs.algs4.StdOut;

/**
 * ���ܣ���¼ÿ���������
 *
 * @author libx
 */
public class Point
{

    private final static double SCALEX = 0.0001 * 1000.0;
    private final static double SCALEY = 0.0001 * 1000.0 * 1.3;

    private int x;//��ĺ�����
    private int y;//���������

    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    //���ص������ֵ
    public String toString()
    {
        return "(" + x + ", " + y + ")";
    }

    //����2�����㲢��������֮��ľ���(ŷ�Ͼ����������ʵ�ʾ���)
    public double distanceTo(Point that)
    {
        double dx = this.x - that.x;
        double dy = this.y - that.y;
        double distance = Math.sqrt(dx * dx + dy * dy);
        return distance;
    }

    //�������λ��
    public void draw()
    {
        Turtle.fly(x * SCALEX, y * SCALEY);
        Turtle.spot(2);
    }

    //��һ�������Ӹõ�����һ��
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

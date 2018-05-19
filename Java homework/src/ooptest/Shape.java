package ooptest;

public class Shape{
    int length=0;
    int wide=0;
    int line=0;
    int list=0;
    public Shape()
    {

    }
    public Shape(int line,int list)
    {
        this.line = line;
        this.list = list;
    }
    public void draw()
    {
        System.out.println("draw");
    }

}

class Rectangle extends Shape{

    public Rectangle()
    {
        super(3,3);
    }
    public void draw()
    {
        System.out.println("draw a rectangle");
    }
}

class Circle extends Shape{
    public  Circle()
    {
        super(4,2);
    }
    public void draw()
    {
        System.out.println("draw a  Circle");
    }
}

class Triangle extends Shape{
    public Triangle()
    {
        super(1,3);
    }
    public void draw()
    {
        System.out.println("draw a  Triangle");
    }
}

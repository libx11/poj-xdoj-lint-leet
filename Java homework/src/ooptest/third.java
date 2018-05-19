package ooptest;

import java.util.Scanner;


class printData
{
    static void printClass(Object obj)
    {
        System.out.println("the class of the Shape is:" + obj.getClass());
    }

}

class third
{
    public static void main(String[] args)
    {
        int num = -1;
        Scanner sr = new Scanner(System.in);

        while (num != 3)
        {
            System.out.println("please input the number of the shape you want");
            System.out.println("0:Rectangle 1:Circle 2:Triangle 3:exit");

            num = sr.nextInt();
            Shape s = new Shape();
            switch (num)
            {
                case 0:
                {
                    s = new Rectangle();//向上转型
                    s.draw();
                    printData.printClass(s);
                    break;
                }
                case 1:
                {
                    s = new Circle();
                    s.draw();
                    printData.printClass(s);
                    break;
                }
                case 2:
                {
                    s = new Triangle();
                    s.draw();
                    printData.printClass(s);
                    break;
                }
                case 3:
                    break;
                default:
                    System.out.println("it's wrong!");
                    break;
            }
        }
        System.out.println("you have exit");
        sr.close();
    }
}

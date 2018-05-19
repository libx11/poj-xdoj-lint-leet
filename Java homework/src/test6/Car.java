package test6;

/**
 * 功能：汽车类
 *
 * @author librah
 */
public class Car
{
    int x, y;
    static int speed = 10;
    int direct;//汽车行驶方向
    boolean stopCar = true;//车辆是否停车
    boolean isStop = true;//停止线程
    static boolean Stop = true;//暂停线程
    boolean isLive = true;

    public Car(int x, int y, int direct)
    {
        this.x = x;
        this.y = y;
        this.direct = direct;
    }
}

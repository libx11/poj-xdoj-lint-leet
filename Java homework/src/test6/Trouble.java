package test6;
import java.awt.Toolkit;
import java.io.IOException;
import java.util.Iterator;

/**
 * 功能：违章车辆
 *
 * @author librah
 */
public class Trouble extends Car implements Runnable
{
    Text text;

    public Trouble(int x, int y, int direct)
    {
        super(x, y, direct);
    }

    public void judge(int x, int y, int direct)
    {
        //碰到边界则将其删除
        if (x < 0 || x > 700 || y < 0 || y > 700)
        {
            this.isStop = false;
            Traffic.tp.init();
        }
        //判断车辆是否碰到灯
        for (int i = 0; i < Traffic.tp.vtLight.size(); i++)
        {
            Light light = Traffic.tp.vtLight.get(i);
            if (direct % 2 == 0)
            {
                if (x >= light.x && x <= light.x + 50 && y >= light.y && y <= light.y + 15)
                {
                    if (light.redLight == true && light.direct == direct)
                    {
                        text = new Text(100, 200, "警告：有人闯红灯");
                        Toolkit.getDefaultToolkit().beep();
                        new Thread(text).start();
                    }
                }
            }
            else if (x >= light.x && x <= light.x + 15 && y >= light.y && y <= light.y + 50)
            {
                if (light.redLight == true && light.direct == direct)
                {
                    text = new Text(100, 200, "警告：有人闯红灯");
                    Toolkit.getDefaultToolkit().beep();
                    new Thread(text).start();
                }
            }
        }
    }

    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        while (true)
        {
            if (Stop)
            {
                switch (direct)
                {
                    case 0:
                        if (stopCar)
                            y += speed;
                        judge(x, y + 35, direct);
                        break;
                    case 1:
                        if (stopCar)
                            x += speed;
                        judge(x + 35, y, direct);
                        break;
                    case 2:
                        if (stopCar)
                            y -= speed;
                        judge(x, y, direct);
                        break;
                    case 3:
                        if (stopCar)
                            x -= speed;
                        judge(x, y, direct);
                        break;
                }
            }
            //如果死亡则退出线程
            if (isStop == false)
                break;
            try
            {
                Thread.sleep(50);
            } catch (InterruptedException e)
            {
                // TODO 自动生成的 catch 块
                e.printStackTrace();
            }
        }

    }
}

package test6;
import java.awt.Color;
import java.util.Iterator;

/**
 * 功能：车的行驶情况判断
 *
 * @author librah
 */
public class MyCar extends Car implements Runnable
{
    //车辆到达十字路口即将开往的方向
    int newDirect;
    Color colorCar;
    public boolean exit = true;

    public MyCar(int x, int y, int direct, int newDirect, Color colorCar)
    {
        super(x, y, direct);
        this.newDirect = newDirect;
        this.colorCar = colorCar;
    }

    //方向改变
    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        while (exit)
        {
            if (Stop)
            {
                switch (direct)
                {
                    case 0:
                        switch (newDirect)
                        {
                            case 1:
                                if (y > 358)
                                    direct = newDirect;
                                break;
                            case 3:
                                if (y > 302)
                                    direct = newDirect;
                                break;
                        }
                        if (stopCar)
                            y += speed;
                        judge(x, y + 35, direct);
                        break;
                    case 1:
                        switch (newDirect)
                        {
                            case 0:
                                if (x > 302)
                                    direct = newDirect;
                                break;
                            case 2:
                                if (x > 358)
                                    direct = newDirect;
                                break;
                        }
                        if (stopCar)
                            x += speed;
                        judge(x + 35, y, direct);
                        break;
                    case 2:
                        switch (newDirect)
                        {
                            case 1:
                                if (y < 385)
                                    direct = newDirect;
                                break;
                            case 3:
                                if (y < 335)
                                    direct = newDirect;
                                break;
                        }
                        if (stopCar)
                            y -= speed;
                        judge(x, y, direct);
                        break;
                    case 3:
                        switch (newDirect)
                        {
                            case 0:
                                if (x < 335)
                                    direct = newDirect;
                                break;
                            case 2:
                                if (x < 385)
                                    direct = newDirect;
                                break;
                        }
                        if (stopCar)
                            x -= speed;
                        judge(x, y, direct);
                        break;
                }
            }
            //碰到边界，则删除该车
            if (x < -100 || x > 910 || y < -100 || y > 910)
            {
                Traffic.tp.vtCar.remove(this);
                this.exit = false;//退出线程
                this.isStop = false;
            }
            Traffic.tp.repaint();
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

    //判断车辆之间是否相撞
    public void judge(int x, int y, int direct)
    {
        Iterator<MyCar> iter = Traffic.tp.vtCar.iterator();
        while (iter.hasNext())
        {
            MyCar mycar = iter.next();
            if (direct % 2 == 0)
            {
                if (x >= mycar.x && x <= mycar.x + 20 && y >= mycar.y && y <= mycar.y + 40)
                {
                    if (mycar.stopCar == false)
                        stopCar = false;
                    else
                        stopCar = true;
                }
                else if (x >= mycar.x && x <= mycar.x + 40 && y >= mycar.y && y <= mycar.y + 20)
                {
                    if (mycar.stopCar == false)
                        stopCar = false;
                    else
                        stopCar = true;
                }
            }
            if (this.isStop == false)
                Traffic.tp.vtCar.remove(mycar);
        }
        //是否碰到交通灯
        for (int i = 0; i < Traffic.tp.vtLight.size(); i++)
        {
            Light light = Traffic.tp.vtLight.get(i);
            if (direct % 2 == 0)
            {
                if (x >= light.x && x <= light.x + 50 && y >= light.y && y <= light.y + 15)
                {
                    if (light.direct == direct)
                    {
                        if (light.redLight == true)
                            stopCar = false;
                        else
                        {
                            stopCar = true;
                            Iterator<MyCar> iter1 = Traffic.tp.vtCar.iterator();
                            while (iter1.hasNext())
                            {
                                MyCar mycar = iter1.next();
                                if (light.direct == mycar.direct)
                                    mycar.stopCar = true;
                            }
                        }

                    }
                }
            }
            else if (x >= light.x && x <= light.x + 15 && y >= light.y && y <= light.y + 50)
            {
                if (light.direct == direct)
                {
                    if (light.redLight == true)
                        stopCar = false;
                    else
                    {
                        stopCar = true;
                        Iterator<MyCar> iter2 = Traffic.tp.vtCar.iterator();
                        while (iter2.hasNext())
                        {
                            MyCar mycar = iter2.next();
                            if (light.direct == mycar.direct)
                                mycar.stopCar = true;
                        }
                    }

                }
            }
        }
    }
}

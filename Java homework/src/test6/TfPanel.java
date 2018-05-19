package test6;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.util.Iterator;
import java.util.Random;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.swing.JPanel;

/**
 * 线程生成交通灯以及车辆
 *
 * @author librah
 */
public class TfPanel extends JPanel implements Runnable
{
    //线程安全的变体，其中所有可变操作都是通过对底层数组进行一次新的复制实现的
    static CopyOnWriteArrayList<MyCar> vtCar = new CopyOnWriteArrayList<MyCar>();//
    static CopyOnWriteArrayList<Light> vtLight = new CopyOnWriteArrayList<Light>();
    Trouble tr = null;
    Random r = new Random();//建立一个随机类，生成伪随机数流
    boolean Stop = true;
    static int carNum = 15;//假设十字路口的车辆为15
    boolean creatMycar = true;

    public TfPanel()
    {
        init();//初始化
        //添加四个交通灯
        vtLight.add(new Light(306, 285, 0));
        vtLight.add(new Light(285, 365, 1));
        vtLight.add(new Light(365, 406, 2));
        vtLight.add(new Light(406, 305, 3));
        //启动交通灯线程
        Thread t = new Thread(new Light());
        t.start();
        //启动交通模拟线程
        new Thread(this).start();
    }

    //生成违章车辆
    public void init()
    {
        switch (r.nextInt(4))
        {
            case 0:
                tr = new Trouble(315, 0, 0);
                break;
            case 1:
                tr = new Trouble(0, 365, 1);
                break;
            case 2:
                tr = new Trouble(365, 700, 2);
                break;
            case 3:
                tr = new Trouble(700, 315, 3);
                break;
        }
        new Thread(tr).start();
    }

    //绘制车辆及交通灯以及路口
    public void paint(Graphics g)
    {
        super.paint(g);
        //画出十字车道
        g.setColor(Color.darkGray);
        g.fillRect(0, 300, 700, 6);
        g.fillRect(0, 400, 700, 6);
        g.fillRect(300, 0, 6, 700);
        g.fillRect(400, 0, 6, 700);
        g.setColor(Color.gray);
        g.fillRect(0, 350, 700, 2);
        g.fillRect(350, 0, 2, 700);
        g.setColor(Color.blue);
        //画出交通灯
        for (int i = 0; i < vtLight.size(); i++)
        {
            Light light = vtLight.get(i);
            g.setColor(Color.black);
            if (light.direct % 2 == 0)
                g.fillRect(light.x, light.y, 35, 15);
            else
                g.fillRect(light.x, light.y, 15, 35);
            //绘制绿灯
            g.setColor(Color.green);
            if (light.greenLight == true)
            {
                if (light.direct % 2 == 0)
                    g.fillOval(light.x, light.y + 2, 10, 10);
                else
                    g.fillOval(light.x + 2, light.y, 10, 10);
            }
            //绘制红灯
            g.setColor(Color.red);
            if (light.redLight == true)
            {
                if (light.direct % 2 == 0)
                    g.fillOval(light.x + 20, light.y + 2, 10, 10);
                else
                    g.fillOval(light.x + 2, light.y + 20, 10, 10);
            }
        }
        //绘制车辆
        Iterator<MyCar> iter = Traffic.tp.vtCar.iterator();
        while (iter.hasNext())
        {
            MyCar mycar = iter.next();
            g.setColor(mycar.colorCar);
            if (mycar.direct % 2 == 0)
                g.fill3DRect(mycar.x, mycar.y, 20, 35, true);
            else
                g.fill3DRect(mycar.x, mycar.y, 35, 20, true);
        }
        //绘制违章车辆
        g.setColor(Color.red);
        if (tr.direct % 2 == 0)
            g.fill3DRect(tr.x, tr.y, 20, 35, true);
        else
            g.fill3DRect(tr.x, tr.y, 35, 20, true);
        //绘制违章警告
        if (tr.text != null)
        {
            g.setFont(new Font("微软雅黑", Font.BOLD, 50));
            g.drawString(tr.text.info, tr.text.x, tr.text.y);
        }
    }

    //得到车辆十字路口的转向
    public int getDirect(int d)
    {
        int i = r.nextInt(4);
        while (true)
        {
            if (i == d)
                i = r.nextInt(4);
            else
                break;
        }
        return i;
    }

    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        MyCar mycar = null;
        int newDirect;
        while (true)
        {
            if (Stop)
            {
                if (vtCar.size() < carNum)
                {
                    if (this.creatMycar)
                    {
                        switch (r.nextInt(4))
                        {
                            case 0:
                                newDirect = getDirect(0);
                                mycar = new MyCar(315, 0, 0, newDirect, Color.blue);
                                vtCar.add(mycar);
                                break;
                            case 1:
                                newDirect = getDirect(1);
                                mycar = new MyCar(0, 365, 1, newDirect, Color.green);
                                vtCar.add(mycar);
                                break;
                            case 2:
                                newDirect = getDirect(2);
                                mycar = new MyCar(365, 700, 2, newDirect, Color.cyan);
                                vtCar.add(mycar);
                                break;
                            case 3:
                                newDirect = getDirect(3);
                                mycar = new MyCar(700, 315, 3, newDirect, Color.orange);
                                vtCar.add(mycar);
                                break;
                        }
                        new Thread(mycar).start();
                    }
                }
            }
            try
            {
                Thread.sleep(5000);
            } catch (InterruptedException e)
            {
                // TODO 自动生成的 catch 块
                e.printStackTrace();
            }
        }
    }

}

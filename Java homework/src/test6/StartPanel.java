package test6;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;

/**
 * 交通道路开始界面
 *
 * @author librah
 */
public class StartPanel extends JPanel implements Runnable
{

    int info = 0;
    boolean isLive = true;

    public void paint(Graphics g)
    {
        super.paint(g);
        g.fillRect(0, 0, 700, 700);
        g.setColor(Color.yellow);
        g.setFont(new Font("微软雅黑", Font.BOLD, 60));
        if (info % 2 == 0)//实现频闪
            g.drawString("十字路口信号灯调度模拟", 0, 300);
    }

    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        while (true)
        {
            try
            {
                Thread.sleep(500);
            } catch (InterruptedException e)
            {
                // TODO: handle exception
                e.printStackTrace();
            }
            info++;
            this.repaint();//重新绘制
            if (isLive == false)
                break;
        }
    }

}

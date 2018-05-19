package test6;/**
 * 功能：十字路口信号灯调度模拟软件
 *
 * @author librah
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Traffic extends JFrame implements ActionListener
{
    static TfPanel tp;
    private JMenuBar jmb = null;
    private JMenu jm1, jm2;
    private JMenuItem jmi1, jmi2, jmi3, jmi4;
    StartPanel sp;

    public static void main(String[] args)
    {
        new Traffic();
    }

    public Traffic()
    {
        jmb = new JMenuBar();//菜单栏
        /*交通模拟器*/
        jm1 = new JMenu("交通模拟");
        jmi1 = new JMenuItem("开始");
        jmi1.addActionListener(this);
        jmi2 = new JMenuItem("暂停");
        jmi2.addActionListener(this);
        jmi3 = new JMenuItem("退出");
        jmi3.addActionListener(this);

        jm1.add(jmi1);
        jm1.add(jmi2);
        jm1.add(jmi3);
        /*控制*/
        jm2 = new JMenu("控制");
        jmi4 = new JMenuItem("设置");
        jmi4.addActionListener(this);
        jm2.add(jmi4);
        /*菜单栏添加选项*/
        jmb.add(jm1);
        jmb.add(jm2);
        this.setJMenuBar(jmb);

        /*交通路口界面*/
        sp = new StartPanel();
        new Thread(sp).start();
        this.add(sp);
        this.setTitle("十字路口信号灯调度模拟软件");
        this.setSize(700, 700);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public void actionPerformed(ActionEvent e)
    {
        // TODO 自动生成的方法存根
        if (e.getSource() == jmi1)
        {
            sp.isLive = false;//关闭开始界面
            this.remove(sp);
            tp = new TfPanel();//打开交通模拟界面
            this.add(tp);
            this.setVisible(true);
        }
        else if (e.getSource() == jmi2)
        {
            if (jmi2.getText().equals("暂停"))
            {
                Car.Stop = false;//车辆暂停
                tp.Stop = false;//交通模拟暂停
                Light.Start = false;//灯的切换关闭
                jmi2.setText("继续");
            }
            else if (jmi2.getText().equals("继续"))
            {
                Car.Stop = true;
                tp.Stop = true;
                Light.Start = true;
                jmi2.setText("暂停");
            }
        }
        else if (e.getSource() == jmi3)//退出程序
            System.exit(0);
        else if (e.getSource() == jmi4)
            new Set(this, "设置", true);
    }

}

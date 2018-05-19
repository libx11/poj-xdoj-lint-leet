package test6;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * 功能：交通模拟车辆设置
 *
 * @author librah
 */
public class Set extends JDialog implements ActionListener
{

    JComboBox jcb1, jcb2;
    JPanel jp1, jp2, jp3;
    JLabel jl1, jl2;
    JButton jb1, jb2;

    public Set(Frame owner, String title, boolean model)
    {
        super(owner, title, model);
        String speed[] = {"5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
        jcb1 = new JComboBox(speed);
        String CarSpeed = Car.speed + "";
        jcb1.setSelectedItem(CarSpeed);//选中汽车行驶速度
        jp1 = new JPanel();
        jl1 = new JLabel("行驶速度为：");
        jp1.add(jl1);
        jp1.add(jcb1);

        jp2 = new JPanel();
        jb1 = new JButton("确定");
        jb1.addActionListener(this);
        jb2 = new JButton("取消");
        jb2.addActionListener(this);
        jp2.add(jb1);
        jp2.add(jb2);

        jp3 = new JPanel();
        jl2 = new JLabel("行驶车辆数目：");
        String carNum[] = {"5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
        jcb2 = new JComboBox(carNum);
        String num = TfPanel.carNum + "";
        jcb2.setSelectedItem(num);
        jp3.add(jl2);
        jp3.add(jcb2);
        this.add(jp1, "North");
        this.add(jp3);
        this.add(jp2, "South");
        this.setSize(200, 200);
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        // TODO 自动生成的方法存根
        if (e.getSource() == jb1)
        {
            Car.speed = Integer.parseInt((String) jcb1.getSelectedItem());
            TfPanel.carNum = Integer.parseInt((String) jcb2.getSelectedItem());
            this.dispose();
        }
        else
            this.dispose();
    }


}

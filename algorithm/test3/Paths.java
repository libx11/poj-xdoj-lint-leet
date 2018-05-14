package test3;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;

/**
 * 功能：显示最短路径
 *
 * @author libx
 */
public class Paths extends JFrame implements ActionListener
{

    private JLabel jl = null;
    private JTextField jtf = null;
    private JButton jb = null;
    private JPanel jp;
    // read in the graph from a file
    In in = new In("E:\\程序\\algorithm\\usa.txt");
    EuclideanGraph G = new EuclideanGraph(in);
    Dijkstra2 dijkstra = new Dijkstra2(G, 5);

    //Dijkstra dijkstra=new Dijkstra(G);
    public Paths()
    {
        Turtle.create(1000, 600);
        G.draw();

        jl = new JLabel("Please input the two points:");
        jtf = new JTextField(10);
        jb = new JButton("Search");
        jb.addActionListener(this);
        jp = new JPanel();
        jp.add(jl);
        jp.add(jtf);
        this.add(jp, "North");
        this.add(jb, "South");

        this.setTitle("最短路径查询");
        this.setSize(300, 200);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);

    }

    public static void main(String[] args)
    {
        new Paths();
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        String str[] = jtf.getText().split(" ");
        int s = Integer.parseInt(str[0]);
        int d = Integer.parseInt(str[1]);
        int V = G.V();
        if (s >= V || d >= V)
        {
            JOptionPane.showMessageDialog(this, "Please input Right points" + "(0~" + V + ")");
            s = Integer.parseInt(str[0]);
            d = Integer.parseInt(str[1]);

        }
        //jtf.setText(null);
        Turtle.clear();
        Turtle.setColor(Color.black);
        Turtle.setStroke(new BasicStroke(1f));
        G.draw();

        Turtle.setColor(Color.red);
        Turtle.setStroke(new BasicStroke(3f));
        dijkstra.showPath(s, d);

        dijkstra.drawPath(s, d);

    }
}

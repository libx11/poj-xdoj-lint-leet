package strsum;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Main
{
    private static Scanner reader;

    public static void main(String[] args) throws IOException
    {
        reader = new Scanner(System.in);

        System.out.println("Please input the name of file:");
        String filename = reader.next();
        System.out.println(filename);
        System.out.println("1 for screen, 2 for file");
        int mode = reader.nextInt();
        //System.out.println(mode);

        //System.out.println(cs);
        int cw = StrStats.countWords(filename);
        int cs = StrStats.countString(filename);
        //System.out.println(cw);
        StringBuilder sb = new StringBuilder();
        if (mode == 2)
        {
            FileWriter fw = new FileWriter("result.txt");
            sb.append("Number of words：" + cw + "\r\n");
            sb.append("Number of strings：" + cs + "\r\n");
            fw.write(sb.toString());
            fw.close();
            System.out.println("Success");
        }
        if (mode == 1)
        {
            System.out.println("Number of words：" + cw);
            System.out.println("Number of strings：" + cs);
        }

    }
}

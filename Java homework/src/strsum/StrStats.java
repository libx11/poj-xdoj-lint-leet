package strsum;

import java.io.*;
import java.util.*;

public class StrStats
{
    private static BufferedReader br;

    public static int countWords(String fileName) throws IOException
    {
        //字母个数统计
        int sum = 0;
        File file = new File("E:\\程序\\Java homework\\src\\strsum", fileName);

        FileReader in = null;
        try
        {
            in = new FileReader(file);
        } catch (FileNotFoundException e)
        {

            System.out.println("Sorry, no such file.");
        }

        int word;
        while ((word = in.read()) != -1)
        {
            if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z'))
                sum++;
        }

        in.close();
        return sum;
    }

    public static int countString(String fileName) throws IOException
    {
        //字符串统计
        File file = new File("E:\\程序\\Java homework\\src\\strsum", fileName);
        int count = 0;
        br = new BufferedReader(new FileReader(file));
        String str = "";
        String string;
        String rl = null;
        while ((rl = br.readLine()) != null)
            str = str + rl;
        br.close();
        Scanner s = new Scanner(str).useDelimiter(" |,|\\?|\\.");
        while (s.hasNext())
        {
            count++;
            s.next();
            //System.out.println(x);
            //System.out.println(s.next());
        }
        s.close();
        return count;
    }

}


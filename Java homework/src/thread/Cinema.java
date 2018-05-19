package thread;

import java.util.Scanner;

public class Cinema
{
    private static Scanner reader;

    public static void main(String[] args)
    {
        reader = new Scanner(System.in);

        System.out.println("可购买的总票数：");
        int total = reader.nextInt();
        System.out.println("单次最大买票数：");
        int singal = reader.nextInt();
        System.out.println("窗口数：");
        int wind = reader.nextInt();
        TicketSell t = new TicketSell(total, singal);
        for (int i = 0; i < wind; i++)
        {
            new Thread(t, String.valueOf(i+1)).start();
        }

    }
}

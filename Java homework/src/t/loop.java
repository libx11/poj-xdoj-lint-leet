package t;

import java.util.Scanner;

public class loop
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);

        System.out.print("WTF");
        int k = in.nextInt();

        System.out.print("WTf");
        int n= in.nextInt();

        int lottert = 1;
        for (int i = 1; i <= k; i++)
        {
            lottert = lottert * (n - i + 1) / i;
        }

        System.out.println(lottert);
    }
}

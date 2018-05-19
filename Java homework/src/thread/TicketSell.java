package thread;

public class TicketSell implements Runnable
{

    public static int TotalTicket;    //总票数
    public int MaxPerSell;        //每次最多卖票数

    public TicketSell(int n, int p)
    {
        TotalTicket = n;
        MaxPerSell = p;
    }

    @Override
    public void run()
    {

        while (true)
        {
            int k = (int) (Math.random() * 400 + 100);        //，每过100到500毫秒卖一次票
            try
            {
                Thread.sleep(k);
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
            int n = (int) (Math.random() * MaxPerSell + 1);
            if (TotalTicket <= 0)
                return;
            synchronized (this)
            {
                if (TotalTicket > n)
                    TotalTicket -= n;
                else
                {
                    n = TotalTicket;
                    TotalTicket = 0;
                }
                System.out.println(Thread.currentThread().getName() + "号窗口卖了" + n + "张，还剩" + TotalTicket + "张");
            }

        }
    }
}


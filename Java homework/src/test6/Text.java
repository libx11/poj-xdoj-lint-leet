package test6;
/**
 * 功能：对违章车辆的处理
 *
 * @author librah
 */
public class Text implements Runnable
{
    static int x, y;
    static String info = "";
    static boolean isLive = false;//设置该违章车的状态
    static int times;

    public Text()
    {
    }

    public Text(int x, int y, String info)
    {
        this.x = x;
        this.y = y;
        this.info = info;
    }

    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        while (true)
        {
            if (isLive)
            {
                try
                {
                    Thread.sleep(3000);
                } catch (InterruptedException e)
                {
                    // TODO 自动生成的 catch 块
                    e.printStackTrace();
                }
                info = "";
                isLive = false;
            }
            if (isLive == false)
                break;
        }
    }


}

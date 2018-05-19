package test6;
/**
 * 功能：实现交通灯
 *
 * @author librah
 */
public class Light implements Runnable
{
    int x, y;
    boolean redLight;//红灯状态
    boolean greenLight;//绿灯状态
    int direct;//方向
    /*红绿灯之间进行切换*/
    static boolean Start = true;
    static boolean Stop = true;

    public Light()
    {
    }

    public Light(int x, int y, int direct)
    {
        this.x = x;
        this.y = y;
        this.direct = direct;
    }

    @Override
    public void run()
    {
        // TODO 自动生成的方法存根
        while (true)
        {
            if (Start)
            {
                for (int i = 0; i < TfPanel.vtLight.size(); i++)
                {
                    Light light = TfPanel.vtLight.get(i);
                    if (light.direct % 2 == 0)
                    {
                        light.greenLight = false;
                        light.redLight = true;
                    }
                    else
                    {
                        light.greenLight = true;
                        light.redLight = false;
                    }
                }
                //切换红绿灯
                this.Start = false;
            }
            else
            {
                for (int i = 0; i < TfPanel.vtLight.size(); i++)
                {
                    Light light = TfPanel.vtLight.get(i);
                    if (light.direct % 2 == 0)
                    {
                        light.greenLight = true;
                        light.redLight = false;
                    }
                    else
                    {
                        light.greenLight = false;
                        light.redLight = true;
                    }
                }
                //切换红绿灯
                this.Start = true;
            }
            try
            {
                Thread.sleep(10000);
            } catch (InterruptedException e)
            {
                // TODO 自动生成的 catch 块
                e.printStackTrace();
            }
        }
    }

}

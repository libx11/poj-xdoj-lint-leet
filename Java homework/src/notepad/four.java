package notepad;

import java.util.*;

public class four
{
    static ArrayList<String> diaryText = new ArrayList<String>();

    public static void showText(ArrayList<String> list, int n)
    {
        if (list.isEmpty())
            System.out.println("尚无记录\n");
        else
        {
            if (n == 0)
                for (int j = 0; j < list.size(); j++)
                    System.out.println((j + 1) + ":" + diaryText.get(j));
            else if (n > 0 && n <= list.size())
                System.out.println(n + ":" + diaryText.get(n - 1));
            else
                System.out.println("输入错误，请重新输入\n");
        }
    }

    public static void deleteText(ArrayList<String> list, int n)
    {
        if (list.isEmpty())
            System.out.println("尚无记录\n");
        else
        {
            if (n == 0)
            {
                list.clear();
                System.out.println("已清除全部记录\n");
            }
            else if (n > 0 && n <= list.size())
            {
                list.remove(n - 1);
                System.out.println("已删除第" + n + "条数据\n");
            }
            else
                System.out.println("输入错误，请重新输入\n");
        }
    }

    public static void isTest()
    {
        int num = 0, i = 0;
        String str;
        Scanner input = new Scanner(System.in);
        System.out.println("记事本功能");
        System.out.println("请输入想要执行的功能");
        while (true)
        {
            System.out.println("1——记事");
            System.out.println("2——已记录数");
            System.out.println("3——追加记录");
            System.out.println("4——显示已存储记录（0为全部记录）");
            System.out.println("5——删除记录（0为全部记录）");
            System.out.println("6——退出");

            num = input.nextInt();

            if (num == 6)
            {
                System.out.println("您已退出程序\n");
                input.close();
                System.exit(0);
            }
            else
                switch (num)
                {
                    case 1:
                    {
                        System.out.println("请输入内容");
                        input.nextLine();
                        str = input.nextLine();
                        diaryText.add(str);
                        System.out.println("已保存\n");
                        break;
                    }
                    case 2:
                    {
                        System.out.println("已记录数为：" + diaryText.size() + "\n");
                        break;
                    }
                    case 3:
                    {
                        System.out.println("请输入修改的记录号");
                        i = input.nextInt();
                        System.out.println("请输入修改内容");
                        input.nextLine();
                        str = input.nextLine();
                        diaryText.set(i - 1, str);
                        System.out.println("已修改\n");
                        break;
                    }
                    case 4:
                    {
                        System.out.println("请输入要显示第几条的内容");
                        i = input.nextInt();
                        showText(diaryText, i);
                        break;
                    }
                    case 5:
                    {
                        System.out.println("请输入要删除第几条的内容");
                        i = input.nextInt();
                        deleteText(diaryText, i);
                        break;
                    }
                    default:
                    {
                        System.out.println("输入错误，请重新输入！\n");
                        break;
                    }
                }
        }
    }

    public static void main(String[] args)
    {
        isTest();
    }
}

package dateprint;

import java.util.Calendar;
import java.util.Scanner;

class CalendarList
{
    int year, month;
    int dayNum, i, num, count = 0;
    Calendar objCalendar;
    int[] arrDayNum = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    CalendarList()
    {
        objCalendar = Calendar.getInstance();
        this.year = objCalendar.get(Calendar.YEAR);
    }

    CalendarList(int args)
    {
        this.year = args;
        objCalendar = Calendar.getInstance();
        objCalendar.set(Calendar.YEAR, year);

    }

    private void displaymonth()
    {
        System.out.println("\t\t\t" + year + "年" + month + "月");
        System.out.println("日    一   二   三   四   五   六");
        num = objCalendar.get(Calendar.DAY_OF_WEEK)-1;

                dayNum = arrDayNum[month - 1];
        for (i = 1, count = 0; i <= num; i++)
        {
            System.out.print("     ");
            count++;
        }
        for (i = 1; i <= dayNum; i++)
        {
            System.out.print(i < 10 ? " " + i + "   " : i + "   ");
            count++;
            if (count == 7)
            {
                System.out.println();
                count = 0;
            }
        }
        System.out.println();
    }

    void display()
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            arrDayNum[1] += 1;
        }
        for (month = 1; month <= 12; month++)
        {
            objCalendar.set(Calendar.MONTH, this.month-1);
            objCalendar.set(Calendar.DAY_OF_MONTH, 1);
            displaymonth();
        }
    }
}

public class sec
{

    public static void main(String[] args)
    {
        System.out.println("input year:");
        Scanner sc = new Scanner(System.in);
        int year = sc.nextInt();
        CalendarList objCalendar = new CalendarList(year);
        objCalendar.display();
    }

}
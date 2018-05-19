package t;

public class list
{
    public static void main(String[] args)
    {
        int size = 10;
        int[] mylist = new int[size];

        for (int i = 0; i < mylist.length; i++)
        {
            mylist[i] = size++;
            System.out.println(mylist[i]);
        }
    }
}

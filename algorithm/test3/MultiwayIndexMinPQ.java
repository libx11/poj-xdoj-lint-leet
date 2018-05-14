package test3;

import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class MultiwayIndexMinPQ<Key> implements Iterable<Integer>
{
    private final int d;                //多路堆堆数
    private int n;                        //队列中当前元素个数
    private int nmax;                    //最大数量
    private int[] pq;                    //元素的键值
    private int[] qp;                    //索引值
    private Key[] keys;                    //元素内容
    private final Comparator<Key> comp; //元素迭代

    @SuppressWarnings("unchecked")
    public MultiwayIndexMinPQ(int N, int D)
    {
        if (N < 0)
            throw new IllegalArgumentException("Maximum number of elements cannot be negative");
        if (D < 2)
            throw new IllegalArgumentException("Dimension should be 2 or over");

        this.d = D;
        nmax = N;

        pq = new int[nmax + D];
        qp = new int[nmax + D];
        keys = (Key[]) new Comparable[nmax + D];

        for (int i = 0; i < nmax + D; qp[i++] = -1)
            ;
        comp = new MyComparator();
    }

    @SuppressWarnings("unchecked")
    public MultiwayIndexMinPQ(int N, Comparator<Key> C, int D)
    {
        if (N < 0)
            throw new IllegalArgumentException("Maximum number of elements cannot be negative");
        if (D < 2)
            throw new IllegalArgumentException("Dimension should be 2 or over");

        this.d = D;
        nmax = N;

        pq = new int[nmax + D];
        qp = new int[nmax + D];
        keys = (Key[]) new Comparable[nmax + D];

        for (int i = 0; i < nmax + D; qp[i++] = -1)
            ;
        comp = C;
    }

    //判断队列是否为空
    public boolean isEmpty()
    {
        return n == 0;
    }

    public boolean contains(int i)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();

        return qp[i + d] != -1;
    }

    //返回队列大小
    public int size()
    {
        return n;
    }

    //插入元素
    public void put(int i, Key key)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (contains(i))
            throw new IllegalArgumentException("Index already there");

        keys[i + d] = key;
        pq[n + d] = i;
        qp[i + d] = n;
        swim(n++);
    }

    public int minIndex()
    {
        if (isEmpty())
            throw new NoSuchElementException("Priority queue is empty");

        return pq[d];
    }

    public Key minKey()
    {
        if (isEmpty())
            throw new NoSuchElementException("Priority queue is empty");

        return keys[pq[d] + d];
    }

    //删除并返回队列中的最小元素
    public int delMin()
    {
        if (isEmpty())
            throw new NoSuchElementException("Priority queue is empty");

        int min = pq[d];
        exch(0, --n);
        sink(0);

        qp[min + d] = -1;
        keys[pq[n + d] + d] = null;
        pq[n + d] = -1;
        return min;
    }

    public Key keyOf(int i)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (!contains(i))
            throw new NoSuchElementException("Specified index is not in the queue");

        return keys[i + d];
    }

    //改变某一键值所对应元素内容
    public void changeKey(int i, Key key)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (!contains(i))
            throw new NoSuchElementException("Specified index is not in the queue");

        Key tmp = keys[i + d];
        keys[i + d] = key;

        if (comp.compare(key, tmp) <= 0)
            swim(qp[i + d]);
        else
            sink(qp[i + d]);
    }

    public void decreaseKey(int i, Key key)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (!contains(i))
            throw new NoSuchElementException("Specified index is not in the queue");
        if (comp.compare(keys[i + d], key) < -10E-6)
            throw new IllegalArgumentException("Calling with this argument would not decrease the Key");

        keys[i + d] = key;
        swim(qp[i + d]);
    }

    public void increaseKey(int i, Key key)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (!contains(i))
            throw new NoSuchElementException("Specified index is not in the queue");
        if (comp.compare(keys[i + d], key) > 10E-6)
            throw new IllegalArgumentException("Calling with this argument would not increase the Key");

        keys[i + d] = key;
        sink(qp[i + d]);
    }

    public void delete(int i)
    {
        if (i < 0 || i >= nmax)
            throw new IllegalArgumentException();
        if (!contains(i))
            throw new NoSuchElementException("Specified index is not in the queue");

        int idx = qp[i + d];
        exch(idx, --n);
        swim(idx);
        sink(idx);
        keys[i + d] = null;
        qp[i + d] = -1;
    }

    //比较键值元素大小
    private boolean greater(int i, int j)
    {
        return comp.compare(keys[pq[i + d] + d], keys[pq[j + d] + d]) > 0;
    }

    //交换两个键值元素
    private void exch(int x, int y)
    {
        int i = x + d, j = y + d;
        int swap = pq[i];

        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i] + d] = x;
        qp[pq[j] + d] = y;
    }

    //上浮操作
    private void swim(int i)
    {
        if (i > 0 && greater((i - 1) / d, i))
        {
            exch(i, (i - 1) / d);
            swim((i - 1) / d);
        }
    }

    //下沉操作
    private void sink(int i)
    {
        if (d * i + 1 >= n)
            return;
        int min = minChild(i);

        while (min < n && greater(i, min))
        {
            exch(i, min);
            i = min;
            min = minChild(i);
        }
    }

    //返回i的最小子节点
    private int minChild(int i)
    {
        int loBound = d * i + 1, hiBound = d * i + d;
        int min = loBound;

        for (int cur = loBound; cur <= hiBound; cur++)
            if (cur < n && greater(min, cur))
                min = cur;

        return min;
    }

    public Iterator<Integer> iterator()
    {
        return new MyIterator();
    }

    //Constructs an Iterator over the indices in linear time
    private class MyIterator implements Iterator<Integer>
    {
        MultiwayIndexMinPQ<Key> clone;

        public MyIterator()
        {
            clone = new MultiwayIndexMinPQ<Key>(nmax, comp, d);
            for (int i = 0; i < n; i++)
                clone.put(pq[i + d], keys[pq[i + d] + d]);
        }

        public boolean hasNext()
        {
            return !clone.isEmpty();
        }

        public Integer next()
        {
            if (!hasNext())
                throw new NoSuchElementException();
            return clone.delMin();
        }

        public void remove()
        {
            throw new UnsupportedOperationException();
        }
    }

    //default Comparator
    private class MyComparator implements Comparator<Key>
    {
        @SuppressWarnings("unchecked")
        public int compare(Key key1, Key key2)
        {
            return ((Comparable<Key>) key1).compareTo(key2);
        }
    }

}
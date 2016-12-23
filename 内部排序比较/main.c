#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAXSIZE 10000   //可排序表的最大长度
#define  max 1000       //基数排序时数据的最大位数；

typedef struct node
{
	int data3;
	int next;
} node;

typedef int DataType[MAXSIZE + 2];
DataType data = { 0 };
DataType datacopy = { 0 };
DataType origin = { 0 };
DataType R1;
int  size;//可排序表的长度
int head;
int fr[10];
int re[10];
long compCount;//统计比较次数
long shiftCount;//统计移动次数

void BeforeSort()//对比较次数和移动次数清零
{
	compCount = 0;
	shiftCount = 0;
}

bool Less(int i, int j)//若表中第i个元素小于第j个元素，则返回True，否则返回False
{
	compCount++;
	return data[i] < data[j];
}

void Swap(int i, int j)//交换表中第i个和第j个元素
{
	int a;
	a = data[i];
	data[i] = data[j];
	data[j] = a;
	shiftCount += 3;
}

void Shift(DataType R, DataType R2, int i, int j)//将R2[j]赋给R[i]
{
	R[i] = R2[j];
	shiftCount++;
}

void CopyData(DataType list1, DataType list2)
{
	memcpy(list2, list1, (size + 1) * sizeof(int));
}

void InverseOrder()//将可排序表置为逆序
{
	int i, j;
	for (i = 1, j = size; i <= size / 2; i++, j--)
	{
		int a;
		a = data[i];
		data[i] = data[j];
		data[j] = a;
	}
	CopyData(data, datacopy);
}

void RandomizeList()//由系统随机一组数
{
	int i;
	printf(" 请输入需要系统生成的待排序表的长度：");
	scanf("%d", &size);
	printf(" 由系统随机产生待排序表的各个算法的比较次数和移动次数如下：\n\n");
	for (i = 1; i <= size; i++)
		data[i] = rand() % (size + 1);
	CopyData(data, datacopy);
	CopyData(data, origin);
}

void HandInit()
{
	int i;
	printf(" 请输入待排序表的长度：");
	scanf("%d", &size);
	printf(" 请输入%d个数据:\n", size);
	for (i = 1; i <= size; i++)
		scanf("%d", &data[i]);
	CopyData(data, datacopy);
	CopyData(data, origin);
	printf(" 手动输入待排序表的各个算法的比较次数和移动次数如下:\n");
}

void output()//输出函数
{
	printf("\t%-16ld%ld\n", compCount, shiftCount);
}

void BubbleSort()//冒泡排序
{
	BeforeSort();
	int swapped, i, m;
	m = size - 1;
	do
	{
		swapped = 0;
		for (i = 1; i <= m; i++)
		{
			if (Less(i + 1, i))
			{
				Swap(i + 1, i);
				swapped = 1;
			}
		}
		m--;
	} while (swapped);
	output();
}

void InsertSort() //插入排序
{
	BeforeSort();
	int i, j;
	for (i = 2; i <= size; i++)
	{
		Shift(data, data, 0, i);
		j = i - 1;
		while (Less(0, j))
		{
			Shift(data, data, j + 1, j);
			j--;
		}
		Shift(data, data, j + 1, 0);
	}
	output();
}

void SelectSort()//选择排序
{
	BeforeSort();
	int i, j, min;
	for (i = 1; i <= size - 1; i++)
	{
		min = i;
		for (j = i + 1; j <= size; j++)
			if (Less(j, min))
				min = j;
		if (i != min)
			Swap(i, min);
	}
	output();
}

int Partition(int low, int high)
{
	int pivotkey;
	Shift(data, data, 0, low);
	pivotkey = data[low];
	while (low < high)
	{
		compCount++;
		while (low < high&&data[high] >= pivotkey)
		{
			compCount++;
			--high;
		}
		Shift(data, data, low, high);
		compCount++;
		while (low < high&&data[low] <= pivotkey)
		{
			compCount++;
			++low;
		}
		Shift(data, data, high, low);
	}
	Shift(data, data, low, 0);
	return low;

}

void QSort(int low, int high)//QuickSort的辅助函数
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(low, high);
		QSort(low, pivotloc - 1);
		QSort(pivotloc + 1, high);
	}
}

void QuickSort()//快速排序
{
	BeforeSort();
	QSort(1, size);
	output();
}

void ShellSort()//希尔排序
{
	BeforeSort();
	int i, j, h;
	i = 4;
	h = 1;
	while (i <= size)
	{
		i = i * 2;
		h = 2 * h + 1;
	}
	while (h != 0)
	{
		i = h;
		while (i <= size)
		{
			j = i - h;
			while (j > 0 && Less(j + h, j))
			{
				Swap(j, j + h);
				j = j - h;
			}
			i++;
		}
		h = (h - 1) / 2;
	}
	output();
}

void Sift(int left, int right)//堆排序的调堆函数
{
	int i, j, finished = 0;
	i = left;
	j = 2 * i;
	Shift(data, data, 0, left);
	Shift(data, data, MAXSIZE + 1, left);
	while (j <= right && !finished)
	{
		if (j < right&&Less(j, j + 1)) j = j + 1;
		if (!Less(0, j)) finished = 1;
		else
		{
			Shift(data, data, i, j);
			i = j;
			j = 2 * i;
		}
	}
	Shift(data, data, i, MAXSIZE + 1);
}

void HeapSort()//堆排序
{
	int left, right;
	BeforeSort();
	for (left = size / 2; left >= 1; left--) Sift(left, size);
	for (right = size; right >= 2; right--)
	{
		Swap(1, right);
		Sift(1, right - 1);
	}
	output();
}

void BInsertSort()//折半插入排序
{
	BeforeSort();
	int i, low, high, m, j;
	for (i = 2; i <= size; i++)
	{
		Shift(data, data, 0, i);
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			m = (low + high) / 2;
			if (Less(0, m)) high = m - 1;
			else low = m + 1;
		}
		for (j = i - 1; j >= high + 1; j--) Shift(data, data, j + 1, j);
		Shift(data, data, high + 1, 0);
	}
	output();
}

void Binsort()//2-路插入排序
{
	BeforeSort();
	int i, k, j;
	int first, last;
	first = last = 1;
	Shift(R1, data, 1, 1);
	for (i = 2; i <= size; i++)
	{
		compCount++;
		if (data[i] >= R1[1])
		{
			compCount++;
			j = last;
			while (j >= 1 && R1[j] > data[i])
			{
				Shift(R1, R1, j + 1, j);
				j--;
				compCount++;
			}
			Shift(R1, data, j + 1, i);
			last++;
		}
		else
		{
			first--;
			if (first == 0) first = size;
			j = first + 1;
			compCount++;
			while (j <= size&&R1[j] <= data[i])
			{
				Shift(R1, R1, j - 1, j);
				j++;
				compCount++;
			}
			Shift(R1, data, j - 1, i);
		}
	}
	k = 1;
	j = first;
	while (k <= size)
	{
		Shift(data, R1, k, j);
		k++;
		j = (j + 1) % (size + 1);
		if (j == 0) j = j + 1;
	}
	output();
}

void Merge(int low, int m, int high)
{
	int i = low, j = m + 1, p = 1;
	while (i <= m&&j <= high)
	{
		if (Less(i, j)) Shift(R1, data, p++, i++);
		else Shift(R1, data, p++, j++);
	}
	while (i <= m)
		Shift(R1, data, p++, i++);
	while (j <= high)
		Shift(R1, data, p++, j++);
	for (p = 1, i = low; i <= high; p++, i++)
		Shift(data, R1, i, p);
}

void MSort(int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		MSort(low, mid);
		MSort(mid + 1, high);
		Merge(low, mid, high);
	}
}

void MergeSort()//归并排序
{
	BeforeSort();
	MSort(1, size);
	output();
}

void Distribute(node *a, int w)
{
	int i;
	for (i = 0; i < 10; i++) fr[i] = -1;
	for (i = head; i != -1; i = a[i].next)
	{
		int x = a[i].data3 / w % 10;
		if (fr[x] == -1)
		{
			fr[x] = re[x] = i;
			compCount++;
		}
		else
		{
			a[re[x]].next = i;
			re[x] = i;
			shiftCount++;
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (fr[i] != -1)
		{
			a[re[i]].next = -1;
		}
	}
}

void Collect(node *a)
{
	int i, last;

	last = -1;
	for (i = 0; i < 10; i++)
	{
		if (fr[i] != -1)
		{
			if (last == -1)
			{
				head = fr[i];
				last = re[i];
			}
			else
			{
				a[last].next = fr[i];
				last = re[i];
				shiftCount++;
			}
		}
	}
	a[last].next = -1;
}

void RadixSort()//基数排序算法。
{
	BeforeSort();

	node* a;
	a = (node *)malloc(size * sizeof(node));
	int i, j = 1;
	for (i = 0; i < size; i++)
	{
		a[i].data3 = data[i + 1];
		a[i].next = i + 1;
	}
	head = 0;
	a[size - 1].next = -1;
	for (i = 1; i <= max; i *= 10)
	{
		Distribute(a, i);
		Collect(a);
	}
	output();
	while (head != -1)
	{
		data[j++] = a[head].data3;
		head = a[head].next;
	}
	printf("\n");

}

void tips()   //操作选择界面
{
	system("cls");//清屏
	printf(" |---------------------------------------------------|\n");
	printf(" |--                    内部排序比较               --|\n");
	printf(" |--                     请选择操作                --|\n");
	printf(" |---------------------------------------------------|\n");
	printf(" |                                                   |\n");
	printf(" |---------------1 使用系统随机数进行测试 -----------|\n");
	printf(" |---------------2  手动输入数据进行测试  -----------|\n");
	printf(" |---------------3    输出排序测试数据    -----------|\n");
	printf(" |---------------0          退出          -----------|\n");
	printf(" |---------------------------------------------------|\n");
	printf(" 请输入要执行的步骤：");
}

void sort_all()//调用全部排序算法
{
	printf("Bubbl: ");
	BubbleSort();
	CopyData(datacopy, data);
	printf("Tnser: ");
	InsertSort();
	CopyData(datacopy, data);
	printf("Selec: ");
	SelectSort();
	CopyData(datacopy, data);
	printf("Quick: ");
	QuickSort();
	CopyData(datacopy, data);
	printf("Shell: ");
	ShellSort();
	CopyData(datacopy, data);
	printf("Heap : ");
	HeapSort();
	CopyData(datacopy, data);
	printf("BInse: ");
	BInsertSort();
	CopyData(datacopy, data);
	printf("Merge: ");
	MergeSort();
	CopyData(datacopy, data);
	printf("Bin  : ");
	Binsort();
	CopyData(datacopy, data);
	printf("Radix: ");
	RadixSort();
	CopyData(data, datacopy);
}

void sort_comp()
{
	int m;
	for (m = 0; m < 3; m++)
	{
		if (m == 0)
			printf(" 乱序：\n");
		else if (m == 1)
			printf(" 正序：\n");
		else
		{
			printf(" 逆序：\n");
			InverseOrder();
		}
		printf("\tcompCount\tshiftCount\n");
		sort_all();
	}
}

void Interpret(int cmd)//处理选项及输入数据
{
	int i;

	switch (cmd)
	{
	case 1:
		RandomizeList();
		sort_comp();
		break;

	case 2:
		HandInit();
		sort_comp();
		break;

	case 3:
		printf("\t");
		for (i = 1; i <= size; i++)
			printf("%d ", origin[i]);
		printf("\n");
		break;

	case 0:
		break;
	}
}

int main()
{
	int cmd;
	do
	{
		tips();
		scanf("%d", &cmd);
		system("cls");   //清屏
		Interpret(cmd);
		printf("按任意键继续···\n");
		getch();
	} while (cmd != 0);
	return 0;
}

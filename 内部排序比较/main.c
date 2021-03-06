#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

#define  MAXDIGIT 100       //基数排序时数据的最大位数；

typedef struct node
{
	int data3;
	int next;
} node;

typedef int * DataType;
DataType data = NULL;
DataType datacopy = NULL;
DataType R1 = NULL;
int size;//可排序表的长度
int head;
int fr[10];
int re[10];
unsigned long long int compCount;//统计比较次数
unsigned long long int shiftCount;//统计移动次数
clock_t start, finish;

void BeforeSort()//对比较次数和移动次数清零
{
	compCount = shiftCount = start = finish = 0;
}

int comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
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

void InitList()  //初始化，申请内存空间
{
	data = (int *)malloc((size + 2) * sizeof(int));
	datacopy = (int *)malloc((size + 2) * sizeof(int));
	R1 = (int *)malloc((size + 2) * sizeof(int));
}

void RandomizeInit()//由系统随机一组数
{
	int i;
	printf(" 请输入需要系统生成的待排序表的长度：");
	scanf("%d", &size);
	InitList();

	printf(" 由系统随机产生待排序表的各个算法的比较次数和移动次数如下：\n\n");
	srand((unsigned)time(NULL) * 10);
	for (i = 1; i <= size; i++)
		data[i] = rand() % (size + 1);
	CopyData(data, datacopy);
}

void HandInit()
{
	int i;
	printf(" 请输入待排序表的长度：");
	scanf("%d", &size);
	InitList();

	printf(" 请输入%d个数据:\n", size);
	for (i = 1; i <= size; i++)
		scanf("%d", &data[i]);
	CopyData(data, datacopy);
	printf(" 手动输入待排序表的各个算法的比较次数和移动次数如下:\n");
}

void output()//输出函数
{
	printf("\t%-16I64u%-16I64u%ld\n", compCount, shiftCount, finish - start);
}

void BubbleSort()//冒泡排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
	output();
}

void InsertSort() //插入排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
	output();
}

void SelectSort()//选择排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
	output();
}

int RandPartition(int p, int q)
{
	//三数取中方法
	int i, m = (p + q) / 2;
	if (Less(p, m))
		Swap(p, m);
	if (Less(q, m))
		Swap(q, m);
	if (Less(q, p))
		Swap(q, p);
	int key = data[p];
	i = p;

	for (int j = p + 1; j <= q; j++)
	{
		if (data[j] <= key)
		{
			i = i + 1;
			if (i != j)
				Swap(i, j);
		}
	}

	Swap(i, p);
	return i;
}
void QSort(int low, int high)//快速排序
{
	if (low < high)
	{
		int k = RandPartition(low, high);
		QSort(low, k - 1);
		QSort(k + 1, high);
	}
}

void QuickSort()//调用快速排序并计时
{
	BeforeSort();
	start = clock();
	QSort(1, size);
	finish = clock();
	output();
}

void ShellSort()//希尔排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
	output();
}

void Sift(int left, int right)//堆排序的调堆函数
{
	int i, j, finished = 0;
	i = left;
	j = 2 * i;
	Shift(data, data, 0, left);
	Shift(data, data, size + 1, left);
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
	Shift(data, data, i, size + 1);
}

void HeapSort()//堆排序
{
	BeforeSort();
	start = clock();
	int left, right;
	for (left = size / 2; left >= 1; left--) Sift(left, size);
	for (right = size; right >= 2; right--)
	{
		Swap(1, right);
		Sift(1, right - 1);
	}
	finish = clock();
	output();
}

void BInsertSort()//折半插入排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
	output();
}

void Binsort()//2-路插入排序
{
	BeforeSort();
	start = clock();
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
	finish = clock();
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
	start = clock();
	MSort(1, size);
	finish = clock();
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
	start = clock();
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
	for (i = 1; i <= MAXDIGIT; i *= 10)
	{
		Distribute(a, i);
		Collect(a);
	}
	finish = clock();
	output();
	while (head != -1)
	{
		data[j++] = a[head].data3;
		head = a[head].next;
	}
	//	printf("");

}

void std_qsort()
{
	BeforeSort();
	start = clock();
	qsort(&data[1], size, sizeof(data[1]), comp);
	finish = clock();
	printf("\t\t\t\t\t%ld\n\n", finish - start);
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
	printf(" |---------------3  输出排序后的测试数据  -----------|\n");
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
	CopyData(datacopy, data);
	printf("Std_q: ");
	std_qsort();
	CopyData(data, datacopy);
}

void sort_comp()
{
	int m = 3;
	while (m--)
	{
		if (m == 2)
			printf(" 乱序：\n");
		else if (m == 1)
			printf(" 正序：\n");
		else
		{
			printf(" 逆序：\n");
			InverseOrder();
		}
		printf("\tcompCount\tshiftCount\ttime(ms)\n");
		sort_all();
	}
}

void Interpret(int cmd)//处理选项及输入数据
{
	int i;

	switch (cmd)
	{
	case 1:
		RandomizeInit();
		sort_comp();
		break;

	case 2:
		HandInit();
		sort_comp();
		break;

	case 3:
		printf("\t");
		for (i = 1; i <= size; i++)
			printf("%d ", datacopy[i]);
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

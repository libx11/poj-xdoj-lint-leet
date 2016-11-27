#include <stdio.h>
#include <stdlib.h>
typedef struct list
{
	int no;
	int data;
	struct list *next;
}List;

List *list_create(int n)//创建n个节点的单向循环链表
{
    List *p, *q, *head;
    int i;
    p = (List *)malloc(sizeof(List));//先创建第1个节点
    head = p;
    printf("请输入n个密码，以空格隔开\n");
    scanf("%d", &p->data);
    p->no = 1;

    for(i = 2; i <= n; i++)//再创建剩余节点
    {
        q = (List *)malloc(sizeof(List));
        q->no = i;
        scanf("%d", &q->data);
        p->next = q;
        p = q;
    }
    p->next = head;//最后一个节点指向头部，形成循环链表
    return head;
}

int main()
{
	int len, n;
	List *p;

	printf("请输入报数上限值m及人数n：\n");
	scanf("%d%d", &n, &len);
	n--;//第一个人数1，数到第n人时，指针指向下一个人的过程有n-1次
	p = list_create(len);

	printf("出列顺序为：\n");
	while(len--)//每次出列1人，循环len次，所有人全部出列
	{
		while(--n)//数到n-1个人处，这里的next更新为第n人处的next的值即可完成出列。
            p = p->next;

        printf("%d ", (p->next)->no);
        n = (p->next)->data;
        p->next = (p->next)->next;
	}
	return 0;
}

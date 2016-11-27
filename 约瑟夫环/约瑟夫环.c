#include <stdio.h>
#include <stdlib.h>
typedef struct list
{
	int no;
	int data;
	struct list *next;
}List;

List *list_create(int n)//����n���ڵ�ĵ���ѭ������
{
    List *p, *q, *head;
    int i;
    p = (List *)malloc(sizeof(List));//�ȴ�����1���ڵ�
    head = p;
    printf("������n�����룬�Կո����\n");
    scanf("%d", &p->data);
    p->no = 1;

    for(i = 2; i <= n; i++)//�ٴ���ʣ��ڵ�
    {
        q = (List *)malloc(sizeof(List));
        q->no = i;
        scanf("%d", &q->data);
        p->next = q;
        p = q;
    }
    p->next = head;//���һ���ڵ�ָ��ͷ�����γ�ѭ������
    return head;
}

int main()
{
	int len, n;
	List *p;

	printf("�����뱨������ֵm������n��\n");
	scanf("%d%d", &n, &len);
	n--;//��һ������1��������n��ʱ��ָ��ָ����һ���˵Ĺ�����n-1��
	p = list_create(len);

	printf("����˳��Ϊ��\n");
	while(len--)//ÿ�γ���1�ˣ�ѭ��len�Σ�������ȫ������
	{
		while(--n)//����n-1���˴��������next����Ϊ��n�˴���next��ֵ������ɳ��С�
            p = p->next;

        printf("%d ", (p->next)->no);
        n = (p->next)->data;
        p->next = (p->next)->next;
	}
	return 0;
}

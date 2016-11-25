#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef struct Stack
{
    char *base;
    char *top;
    int stacksize;
}stack;

void InitStack(stack s) //����ջ
{
    s.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
}

void Push(stack s,char e) //ѹ��Ԫ��
{
    if(s.top-s.base>=STACK_INIT_SIZE)
    {
        s.base = (char*)realloc(s.base,(s.stacksize+STACK_INCREMENT)*sizeof(char));
        s.top = s.base+s.stacksize;
        s.stacksize += STACK_INCREMENT;
    }
    *(s.top) = e;
    s.top++;

}
void Pop(stack s,char *e) //ȡ��Ԫ��
{
    e = --s.top;
}

int StackEmpty(stack s) //ջ�Ƿ�Ϊ��
{
    if(s.top == s.base)
        return 1;
    else
        return 0;
}

void ClearStack(stack s)
{
    s.top = s.base;
}

typedef struct Queue
{
    char data;
    struct Queue* next;
}queue;

typedef struct LinkQueue
{
    queue *front;
    queue *rear;
}linkqueue;

void InitQueue(linkqueue q) //�����
{
    q.front = q.rear = (queue*)malloc(sizeof(queue));
    q.front->next=NULL;
}

void EnQueue(linkqueue q,char e) //Ԫ�����
{
    queue *p;
    p = (queue*)malloc(sizeof(queue));
    p->data = e;
    p->next=NULL;
    q.rear->next = p;
    q.rear = p;
}

void DeQueue(linkqueue q,char *e) //Ԫ�س���
{
    queue *p;
    p = q.front->next;
    e = &(p->data);
    q.front->next=p->next;
    if(q.rear == p)
        q.rear = q.front;
    free(p);
}

int QueueEmpty(linkqueue q) //���Ƿ�Ϊ��
{
    if(q.front == q.rear)
        return 1;
    else
        return 0;
}


void InStack(char* ch,stack s) //���ַ������������ѹ��ջ��
{
    int i, L;
    L = strlen(ch);

}

void translate(char *origin)
{
    int i, j, len;
    stack s;
    stack temp;//���������������Ԫ��
    InitStack(S);
    InitStack(temp);
    linkqueue Q;
    InitQueue(Q);

    char A[]="sae";
    char B[]="tsaedsae";

    len = strlen(origin);
    for(i = len-1; i >= 0; i--)
    {
        if(ch[i] == '(')
            while(ch[i++] != ')')
            {
                Pop(s);
            }
        else
            Push(s, ch[i]);

    }

}

int main()
{
    int i=0;
    char A[]="sae";
    char B[]="tsaedsae";
    char flag='0';//flag������Ǵ�������
    int mark=1;
    int f=0;

    char MoWang[100]="\0";
    char e1,key,e2,e;
    printf("����������Ҫ���͵�ħ�����ԣ���ຬ��һ�����ţ���\n");
    gets(MoWang);

    translate(MoWang);

    while(!StackEmpty(S))
    {
        Pop(S,e1);

        if(e1=='(')
        {
            if(StackEmpty(S))
            {
                printf("ħ�����Դ���!\n");
                mark=0;
                break;
            }

            while(!StackEmpty(S))
            {
                Pop(S,e1);

                if(e1==')')
                {
                    f=1;
                    break;
                }
                else if(!(e1>='a'&&e1<='z')&&!(e1>='A'&&e1<='Z'))
                {
                    printf("ħ�����Դ���\n");
                    mark=0;
                    break;
                }
            }

            if(mark==0)
                break;

            if(f!=1)
            {
                printf("ħ�����Դ���\n");
                break;
            }
        }

        else if(e1==')')
        {
            printf("ħ�����Դ���\n");
            mark=0;
            break;
        }

        else if(!(e1>='a'&&e1<='z')&&!(e1>='A'&&e1<='Z'))
        {
            printf("ħ�����Դ���\n");
            mark=0;
            break;
        }

    }

    if(mark==1&&f==1)
    {

        ClearStack(S);
        InStack(MoWang,S);

        while(!StackEmpty(S)) //ջ����ʱ
        {

            Pop(S,e1);

            if(e1=='B')
                Push(temp,e1);
            else if(e1=='A')
                Push(temp,e1);

            else if(e1=='(') //�öӴ洢�����е�Ԫ��
            {
                Push(temp,flag);//�����ŵĻ�����flag���
                Pop(S,e1);

                while(e1!=')')
                {
                    EnQueue(Q,e1);
                    Pop(S,e1);
                }

                if(!QueueEmpty(Q))
                    DeQueue(Q,key);
            }

            else
            {
                Push(temp,e1);
                f=0;
            }
        }

        while(!StackEmpty(temp)) //�ߴ���߽�ջ
        {
            Pop(temp,e1);

            if(e1!=flag) //���������Ԫ��ѹ����
                Push(S,e1);
            else
            {
                while(!QueueEmpty(Q)) //���������е�Ԫ�ؽ�ջ
                {
                    DeQueue(Q,e2);
                    Push(S,key);
                    Push(S,e2);
                }

                if(f!=0) //���Ҫѹһ��key
                    Push(S,key);
            }
        }

        printf("���ͺ������Ϊ��\n");

        while(!StackEmpty(S)) //���γ�ջ���������Ԫ��
        {
            Pop(S,e);
            EnQueue(Q,e);//Ԫ�ؽ�����Ϊ�������Ӧ����

            if(e=='B')
                printf("%s",B);
            else if(e=='A')
                printf("%s",A);
            else
                printf("%c",e);
        }

        printf("\n");

        while(!QueueEmpty(Q)) //�����Ӧ����
        {
            DeQueue(Q,e);

            switch(e)
            {
            case 't':
                printf("��");
                break;
            case 'd' :
                printf("��");
                break;
            case 's' :
                printf("��");
                break;
            case 'a' :
                printf("һֻ");
                break;
            case 'e' :
                printf("��");
                break;
            case 'z' :
                printf("׷");
                break;
            case 'g' :
                printf("��");
                break;
            case 'x' :
                printf("��");
                break;
            case 'n' :
                printf("��");
                break;
            case 'h' :
                printf("��");
                break;
            case 'B' :
                printf("����һֻ�����һֻ��");
                break;
            case 'A' :
                printf("��һֻ��");
                break;
            default :
                printf("*");
                break;
            }
        }
        printf("\n");
    }
    return 0;
}

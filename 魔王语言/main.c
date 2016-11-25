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

void InitStack(stack s) //构造栈
{
    s.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
}

void Push(stack s,char e) //压入元素
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
void Pop(stack s,char *e) //取出元素
{
    e = --s.top;
}

int StackEmpty(stack s) //栈是否为空
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

void InitQueue(linkqueue q) //构造队
{
    q.front = q.rear = (queue*)malloc(sizeof(queue));
    q.front->next=NULL;
}

void EnQueue(linkqueue q,char e) //元素入队
{
    queue *p;
    p = (queue*)malloc(sizeof(queue));
    p->data = e;
    p->next=NULL;
    q.rear->next = p;
    q.rear = p;
}

void DeQueue(linkqueue q,char *e) //元素出队
{
    queue *p;
    p = q.front->next;
    e = &(p->data);
    q.front->next=p->next;
    if(q.rear == p)
        q.rear = q.front;
    free(p);
}

int QueueEmpty(linkqueue q) //队是否为空
{
    if(q.front == q.rear)
        return 1;
    else
        return 0;
}


void InStack(char* ch,stack s) //把字符数组从右至左压入栈中
{
    int i, L;
    L = strlen(ch);

}

void translate(char *origin)
{
    int i, j, len;
    stack s;
    stack temp;//用来处理括号外的元素
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
    char flag='0';//flag用来标记处理括号
    int mark=1;
    int f=0;

    char MoWang[100]="\0";
    char e1,key,e2,e;
    printf("请输入你想要解释的魔王语言（最多含有一个括号）：\n");
    gets(MoWang);

    translate(MoWang);

    while(!StackEmpty(S))
    {
        Pop(S,e1);

        if(e1=='(')
        {
            if(StackEmpty(S))
            {
                printf("魔王语言错误!\n");
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
                    printf("魔王语言错误！\n");
                    mark=0;
                    break;
                }
            }

            if(mark==0)
                break;

            if(f!=1)
            {
                printf("魔王语言错误！\n");
                break;
            }
        }

        else if(e1==')')
        {
            printf("魔王语言错误！\n");
            mark=0;
            break;
        }

        else if(!(e1>='a'&&e1<='z')&&!(e1>='A'&&e1<='Z'))
        {
            printf("魔王语言错误！\n");
            mark=0;
            break;
        }

    }

    if(mark==1&&f==1)
    {

        ClearStack(S);
        InStack(MoWang,S);

        while(!StackEmpty(S)) //栈不空时
        {

            Pop(S,e1);

            if(e1=='B')
                Push(temp,e1);
            else if(e1=='A')
                Push(temp,e1);

            else if(e1=='(') //用队存储括号中的元素
            {
                Push(temp,flag);//有括号的话就用flag标记
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

        while(!StackEmpty(temp)) //边处理边进栈
        {
            Pop(temp,e1);

            if(e1!=flag) //把括号外的元素压入中
                Push(S,e1);
            else
            {
                while(!QueueEmpty(Q)) //处理括号中的元素进栈
                {
                    DeQueue(Q,e2);
                    Push(S,key);
                    Push(S,e2);
                }

                if(f!=0) //最后还要压一个key
                    Push(S,key);
            }
        }

        printf("解释后的语言为：\n");

        while(!StackEmpty(S)) //依次出栈输出处理后的元素
        {
            Pop(S,e);
            EnQueue(Q,e);//元素进队是为了输出对应汉字

            if(e=='B')
                printf("%s",B);
            else if(e=='A')
                printf("%s",A);
            else
                printf("%c",e);
        }

        printf("\n");

        while(!QueueEmpty(Q)) //输出对应汉字
        {
            DeQueue(Q,e);

            switch(e)
            {
            case 't':
                printf("天");
                break;
            case 'd' :
                printf("地");
                break;
            case 's' :
                printf("上");
                break;
            case 'a' :
                printf("一只");
                break;
            case 'e' :
                printf("鹅");
                break;
            case 'z' :
                printf("追");
                break;
            case 'g' :
                printf("赶");
                break;
            case 'x' :
                printf("下");
                break;
            case 'n' :
                printf("蛋");
                break;
            case 'h' :
                printf("恨");
                break;
            case 'B' :
                printf("天上一只鹅地上一只鹅");
                break;
            case 'A' :
                printf("上一只鹅");
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

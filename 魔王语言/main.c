#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef struct Stack
{
    char *base;
    char *top;
    int stacksize;
}stack;

void InitStack(stack *s) //初始化栈
{
    s->base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
}

void Push(stack *s,char e) //压入元素
{
    if(s->top-s->base >= STACK_INIT_SIZE)
    {
        s->base = (char *)realloc(s->base,(s->stacksize+STACK_INCREMENT)*sizeof(char));
        s->top = s->base+s->stacksize;
        s->stacksize += STACK_INCREMENT;
    }

    *(s->top) = e;
    s->top++;

}
void Pop(stack *s, char *e) //取出元素
{
    *e = *--(s->top);
}

int StackEmpty(stack *s) //栈是否为空
{
    if(s->top == s->base)
        return 1;
    else
        return 0;
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

void InitQueue(linkqueue *q) //初始化队
{
    q->front = q->rear = (queue*)malloc(sizeof(queue));
    q->front->next=NULL;
}

void EnQueue(linkqueue *q,char e) //元素入队
{
    queue *p;
    p = (queue*)malloc(sizeof(queue));
    p->data = e;
    p->next=NULL;
    q->rear->next = p;
    q->rear = p;
}

void DeQueue(linkqueue *q,char *e) //元素出队
{
    queue *p;
    p = q->front->next;
    *e = p->data;
    q->front->next=p->next;
    if(q->rear == p)
        q->rear = q->front;
    free(p);
}

int QueueEmpty(linkqueue q) //队是否为空
{
    if(q.front == q.rear)
        return 1;
    else
        return 0;
}

void advance_push(stack *s, char e)//处理AB字符
{
    int i;
    char A[]="sae";
    char B[]="tsaedsae";
    if(e == 'A')
        for(i = strlen(A); i > 0; i--)
            Push(s, A[i-1]);
    else if(e == 'B')
        for(i = strlen(B); i > 0; i--)
            Push(s, B[i-1]);
    else
        Push(s, e);
}

void translate(stack *s, char origin[])//处理括号
{
    int i, len;
    linkqueue q;
    InitQueue(&q);
    char repeat, temp;

    len = strlen(origin);
    for(i = len-1; i >= 0; i--)
    {
        if(origin[i] == '(')//处理括号内的内容
        {
            while(1)
            {
                Pop(s, &temp);
                if(temp == ')')
                    break;
                EnQueue(&q, temp);
            }

            DeQueue(&q, &repeat);
            while(!QueueEmpty(q))
            {
                advance_push(s, repeat);
                DeQueue(&q, &temp);
                advance_push(s, temp);
            }
            advance_push(s, repeat);

        }
        else
            advance_push(s, origin[i]);
    }
}

void print_stack(stack *s)
{
    linkqueue q;
    InitQueue(&q);
    char e;

    if(!StackEmpty(s))
    {
        printf("解释后的语言为：\n");

        while(!StackEmpty(s)) //依次出栈输出处理后的元素
        {
            Pop(s, &e);
            EnQueue(&q, e);//元素进队是为了输出对应汉字
            printf("%c",e);
        }

        printf("\n进一步解释为汉字：\n");

        while(!QueueEmpty(q)) //输出对应汉字
        {
            DeQueue(&q, &e);

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
            default :
                printf("*");
                break;
            }
        }
        printf("\n");
    }
}

int main()
{
    stack s;
    InitStack(&s);
    char origin[100]="\0";

    printf("请输入你想要解释的魔王语言：\n");
    gets(origin);
    translate(&s, origin);
    print_stack(&s);
    return 0;
}

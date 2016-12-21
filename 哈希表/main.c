#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAXLEN 30
#define HASH_LENGTH 50               //��ϣ��ĳ���
#define M 47                         //ȡ�������
#define NAME_NO 30                   //�����ĸ���

typedef struct
{
    char *py;    //���ֵ�ƴ��
    int k;       //��������Ӧ�Ĺؼ���
} NAME;

NAME NameList[HASH_LENGTH];    //ȫ�ֱ���NAME

typedef struct    //��ϣ��
{
    char *py;   //���ֵ�ƴ��
    int k;      //ƴ������Ӧ������
    int si;     //���ҳ���
} HASH;

HASH HashList[HASH_LENGTH];        //ȫ�ֱ���HASH


/*�������ṹ�����飩��ʼ�� */
void InitNameList()
{
    char *f;
    int r,s0,i;
    for (i=0; i<HASH_LENGTH; i++)
    {
        NameList[i].py = (char *)malloc(NAME_MAXLEN * sizeof(char));
        NameList[i].py[0] = 0;
    }
    printf(" ����30��������ƴ�����Իس�����\n");
    for(i=0; i<NAME_NO; i++)
    {
        s0=0;
        gets(NameList[i].py);
        f=NameList[i].py;
        for(r=0; *(f+r)!='\0'; r++)     /* ���������ַ����ĸ����ַ�����Ӧ��ASCII����ӣ����õ�������Ϊ��ϣ��Ĺؼ���*/
            s0=*(f+r)+s0;
        NameList[i].k=s0;
    }
    printf(" ������ɣ���������������˵�");
    getch();
}

/*������ϣ��*/
void CreateHashList()
{
    int i;
    for(i=0; i<HASH_LENGTH; i++)
    {
        HashList[i].py=(char *)malloc(NAME_MAXLEN * sizeof(char));
        HashList[i].py[0] = 0;
        HashList[i].k=0;
        HashList[i].si=0;
    }
    for(i=0; i<HASH_LENGTH; i++)
    {
        int sum=0;
        int adr=(NameList[i].k)%M;      //��ϣ����

        int d=adr;
        if(HashList[adr].si==0)     //�������ͻ
        {
            HashList[adr].k=NameList[i].k;
            HashList[adr].py=NameList[i].py;
            HashList[adr].si=1;
        }
        else   //��ͻ
        {
            while (HashList[d].k!=0)
            {
                d=(d+NameList[i].k%10+1)%M;   //�����ͻ
                sum=sum+1;                    //���Ҵ�����1
            };
            HashList[d].k=NameList[i].k;
            HashList[d].py=NameList[i].py;
            HashList[d].si=sum+1;
        }
    }
}

/*����ģ��*/
void FindList()
{
    char name[NAME_MAXLEN];
    int s0=0,r,sum=1,adr,d;
    printf("������Ҫ���ҵ�����ƴ��");
    getchar();                   //���ջس�
    gets(name);
    for(r=0; name[r]!='\0'; r++) //���������ƴ������Ӧ������(�ؼ���)
        s0+=name[r];

    adr=s0%M;   //ʹ�ù�ϣ����
    d=adr;
    if(HashList[adr].k==s0)          //��3����������ж�
        printf("����:%s\t�ؼ���:%d\t���ҳ���Ϊ: 1\n", HashList[d].py, s0);
    else if (HashList[adr].k==0)
        printf("�޴˼�¼!");
    else
    {

        int g=0;
        while(g==0)
        {
            d=(d+s0%10+1)%M;       //�����ͻ
            sum=sum+1;
            if(HashList[d].k==0)
            {
                printf("�޴˼�¼!");
                g=1;
            }

            if(HashList[d].k==s0)
            {
                printf("����:%s\t�ؼ���:%d\t���ҳ���Ϊ: %d\n", HashList[d].py, s0, sum);
                g=1;
            }
        }
    }
    printf(" ��������������˵�");
    getch();
}

/* ��ʾ��ϣ��  */
void   Display()
{
    int i;
    float average=0;

    printf("\n��ַ\t�ؼ���\t��������\tH(key)\t ����\n"); //��ʾ�ĸ�ʽ
    for(i=0; i<50; i++)
    {
        printf("%d\t%d\t%d\t\t%d\t%s\n", i, HashList[i].k, HashList[i].si, HashList[i].k%M, HashList[i].py);
    }
    for(i=0; i<HASH_LENGTH; i++)
        average+=HashList[i].si;
    average/=NAME_NO;
    printf("ƽ�����ҳ��ȣ�ASL(%d)=%f\n", NAME_NO, average);
    printf(" ��������������˵�");
    getch();
}
void tips()   //����ѡ�����
{
    printf(" |---------------------------------------------------|\n");
    printf(" |--                      �����б�                 --|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" |                                                   |\n");
    printf(" |-------------------1   ��ӡ��ϣ��   ---------------|\n");
    printf(" |-------------------2      ����      ---------------|\n");
    printf(" |-------------------0      �˳�      ---------------|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" ��ѡ��");
}
/*�������������������ܺ���*/
int main()
{
    char x;
    int i;
    InitNameList();
    CreateHashList ();

    while(1)
    {
        system("cls");
        tips();
        scanf("%c", &x);
        system("cls");
        if(x=='1')
            Display();
        else if(x=='2')
            FindList();
        else if(x=='0')
            break;
        else
            printf("input error");
    }
    return 0;
}

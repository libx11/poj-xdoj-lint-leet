#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAXLEN 30
#define HASH_LENGTH 50               //哈希表的长度
#define M 47                         //取余随机数
#define NAME_NO 30                   //人名的个数

typedef struct
{
    char *py;    //名字的拼音
    int k;       //名字所对应的关键字
} NAME;

NAME NameList[HASH_LENGTH];    //全局变量NAME

typedef struct    //哈希表
{
    char *py;   //名字的拼音
    int k;      //拼音所对应的整数
    int si;     //查找长度
} HASH;

HASH HashList[HASH_LENGTH];        //全局变量HASH


/*姓名（结构体数组）初始化 */
void InitNameList()
{
    char *f;
    int r,s0,i;
    for (i=0; i<HASH_LENGTH; i++)
    {
        NameList[i].py = (char *)malloc(NAME_MAXLEN * sizeof(char));
        NameList[i].py[0] = 0;
    }
    printf(" 输入30个人名的拼音，以回车结束\n");
    for(i=0; i<NAME_NO; i++)
    {
        s0=0;
        gets(NameList[i].py);
        f=NameList[i].py;
        for(r=0; *(f+r)!='\0'; r++)     /* 方法：将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字*/
            s0=*(f+r)+s0;
        NameList[i].k=s0;
    }
    printf(" 输入完成，按任意键进入主菜单");
    getch();
}

/*建立哈希表*/
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
        int adr=(NameList[i].k)%M;      //哈希函数

        int d=adr;
        if(HashList[adr].si==0)     //如果不冲突
        {
            HashList[adr].k=NameList[i].k;
            HashList[adr].py=NameList[i].py;
            HashList[adr].si=1;
        }
        else   //冲突
        {
            while (HashList[d].k!=0)
            {
                d=(d+NameList[i].k%10+1)%M;   //处理冲突
                sum=sum+1;                    //查找次数加1
            };
            HashList[d].k=NameList[i].k;
            HashList[d].py=NameList[i].py;
            HashList[d].si=sum+1;
        }
    }
}

/*查找模块*/
void FindList()
{
    char name[NAME_MAXLEN];
    int s0=0,r,sum=1,adr,d;
    printf("请输入要查找的姓名拼音");
    getchar();                   //吸收回车
    gets(name);
    for(r=0; name[r]!='\0'; r++) //求出姓名的拼音所对应的整数(关键字)
        s0+=name[r];

    adr=s0%M;   //使用哈希函数
    d=adr;
    if(HashList[adr].k==s0)          //分3种情况进行判断
        printf("姓名:%s\t关键字:%d\t查找长度为: 1\n", HashList[d].py, s0);
    else if (HashList[adr].k==0)
        printf("无此记录!");
    else
    {

        int g=0;
        while(g==0)
        {
            d=(d+s0%10+1)%M;       //处理冲突
            sum=sum+1;
            if(HashList[d].k==0)
            {
                printf("无此记录!");
                g=1;
            }

            if(HashList[d].k==s0)
            {
                printf("姓名:%s\t关键字:%d\t查找长度为: %d\n", HashList[d].py, s0, sum);
                g=1;
            }
        }
    }
    printf(" 按任意键返回主菜单");
    getch();
}

/* 显示哈希表  */
void   Display()
{
    int i;
    float average=0;

    printf("\n地址\t关键字\t搜索长度\tH(key)\t 姓名\n"); //显示的格式
    for(i=0; i<50; i++)
    {
        printf("%d\t%d\t%d\t\t%d\t%s\n", i, HashList[i].k, HashList[i].si, HashList[i].k%M, HashList[i].py);
    }
    for(i=0; i<HASH_LENGTH; i++)
        average+=HashList[i].si;
    average/=NAME_NO;
    printf("平均查找长度：ASL(%d)=%f\n", NAME_NO, average);
    printf(" 按任意键返回主菜单");
    getch();
}
void tips()   //操作选择界面
{
    printf(" |---------------------------------------------------|\n");
    printf(" |--                      操作列表                 --|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" |                                                   |\n");
    printf(" |-------------------1   打印哈希表   ---------------|\n");
    printf(" |-------------------2      查找      ---------------|\n");
    printf(" |-------------------0      退出      ---------------|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" 请选择：");
}
/*主函数，调用其他功能函数*/
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

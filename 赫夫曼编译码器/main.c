#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义赫夫曼树结点的结构体
typedef struct
{
    char ch;                //增加一个域，存放该节点的字符
    int weight;
    int parent,lchild,rchild;
} HTNode,*HuffmanTree;
typedef char **HuffmanCode;   //指向赫夫曼编码的指针

HuffmanTree HT;    //全局变量
int n=0;    //全局变量，存放赫夫曼树叶子结点的数目

void tips()   //操作选择界面
{
    printf(" |---------------------------------------------------|\n");
    printf(" |--                     请选择操作                --|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" |                                                   |\n");
    printf(" |-------------------1 初始化赫夫曼树 ---------------|\n");
    printf(" |-------------------2      编码      ---------------|\n");
    printf(" |-------------------3      译码      ---------------|\n");
    printf(" |-------------------4  打印代码文件  ---------------|\n");
    printf(" |-------------------5  打印赫夫曼树  ---------------|\n");
    printf(" |-------------------0      退出      ---------------|\n");
    printf(" |---------------------------------------------------|\n");
}

//从HT[1]到HT[j]中选择parent为0，weight最小的两个结点，用x和y返回其序号
void select(int j,int *x,int *y)
{
    int i;
//查找weight最小的结点
    for (i=1; i<=j; i++)
        if (HT[i].parent==0)
        {
            *x=i;
            break;
        }
    for (; i<=j; i++)
        if ((HT[i].parent==0)&&(HT[i].weight<HT[*x].weight))
            *x=i;
    HT[*x].parent=1;
//查找weight次小的结点
    for (i=1; i<=j; i++)
        if (HT[i].parent==0)
        {
            *y=i;
            break;
        }
    for (; i<=j; i++)
        if ((HT[i].parent==0)&&(i!=*x)&&(HT[i].weight<HT[*y].weight))
            *y=i;

}

//建立赫夫曼树的算法
void HuffmanCoding(char *character,int *w,int n)
{
    int m,i,x,y;
    HuffmanTree p;
    if(n<=1) return;
    m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(p=HT+1,i=1; i<=n; ++i,++p,++character,++w)
    {
        p->ch=*character;
        p->weight=*w;
        p->parent=0;
        p->lchild=0;
        p->rchild=0;
    }
    for(; i<=m; ++i,++p)
    {
        p->ch=0;
        p->weight=0;
        p->parent=0;
        p->lchild=0;
        p->rchild=0;
    }
    for(i=n+1; i<=m; ++i)
    {
        select(i-1,&x,&y);
        HT[x].parent=i;
        HT[y].parent=i;
        HT[i].lchild=x;
        HT[i].rchild=y;
        HT[i].weight=HT[x].weight+HT[y].weight;
    }

}

void Convert_tree(unsigned char T[100][100],int s,int *i,int j)//将文件中的赫夫曼树转换成凹入表形式的赫夫曼树打印出来
{
    int k,l;
    if(HT[j].rchild)//最上边一行输出的是最右的节点，故采用中序遍历，这里是递归遍历右节点
        Convert_tree(T,s+1,i,HT[j].rchild);

    l=++(*i);       //读取节点数据并存入数组
    for(k=0; k<s; k++)
        T[l][k]=' ';
    T[l][k]=HT[j].weight;
    if(HT[j].rchild)//有子节点就在后边输出一个字符以便观察
        T[l][++k]='<';
    else
        T[l][++k]=' ';
    T[l][++k]=0;


    if(HT[j].lchild)//递归遍历左节点
        Convert_tree(T,s+1,i,HT[j].lchild);

}

//从文件hfmtree.txt中读入赫夫曼树，返回叶子节点数
int Read_tree()
{
    FILE *fp;
    int i,n;
    HT=(HuffmanTree)malloc(sizeof(HTNode));
    if((fp=fopen("hfmtree.txt","r"))==NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i=1; !feof(fp); i++)
    {
        HT=(HuffmanTree)realloc(HT,(i+1)*sizeof(HTNode));   //增加空间
        fread(&HT[i],sizeof(HTNode),1,fp);   //读入一个节点信息
    }
    fclose(fp);
    n=(i-1)/2;
    return n;
}

//译码时根据01字符串寻找相应叶子节点的递归算法
void find(char *code,char *text,int i,int m)
{

    if(*code!='\0')    //若译码未结束
    {
        code++;
        if(HT[i].lchild==0&&HT[i].rchild==0)   //若找到叶子节点
        {

            *text=HT[i].ch;   //将叶子节点的字符存入text中

            text++;
            if((*code=='0'))
                find(code,text,HT[m].lchild,m);    //从根节点的左子树找
            else
                find(code,text,HT[m].rchild,m);    //从根节点的右子树找
        }
        else   //如果不是叶子节点
            if(*code=='0')
                find(code,text,HT[i].lchild,m);   //从该节点的左子树去找
            else
                find(code,text,HT[i].rchild,m);   //从该节点的右子树去找
    }
    else
        *text='\0'; //译码结束

}

//初始化函数，输入n个字符及其对应的权值，根据权值建立哈夫曼树，并将其存于文件hfmtree中
void Init()
{
    FILE *fp;
    int i,n,w[52];    //数组存放字符的权值
    char character[52];    //存放n个字符
    printf("\n输入字符个数 n:\n");
    scanf("%d",&n);        //输入字符集大小
    printf("输入%d个字符及其对应的权值:\n",n);
    for (i=0; i<n; i++)
    {
        scanf(" %c",&character[i]);
        scanf("%d",&w[i]);           //输入n个字符和对应的权值
    }
    HuffmanCoding(character,w,n);    //建立赫夫曼树

    if((fp=fopen("hfmtree.txt","w"))==NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i=1; i<=2*n-1; i++)
    {
        if(fwrite(&HT[i],sizeof(HTNode),1,fp)!=1)   //将建立的赫夫曼树存入文件hfmtree.txt中
            printf("File write error!\n");
    }
    printf("\n赫夫曼树建立成功，并已存于文件hfmtree.txt中\n");
    fclose(fp);
}

//对文件tobetrans中的正文进行编码，然后将结果存入文件codefile中
void Coding()
{
    FILE *fp,*fw;
    int i,f,c,r, start;
    char *cd;
    HuffmanCode HC;
    if(n==0)
        n=Read_tree(HT);//从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数

//求赫夫曼树中各叶子节点的字符对应的的编码，并存于HC指向的空间中
    {
        HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
        cd=(char *)malloc(n*sizeof(char));
        cd[n-1]='\0';
        for(i=1; i<=n; ++i)
        {
            start=n-1;
            for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
                if(HT[f].lchild==c)
                    cd[--start]='0';
                else cd[--start]='1';
            HC[i]=(char *)malloc((n-start)*sizeof(char));
            strcpy(HC[i],&cd[start]);
        }
        free(cd);
    }


    if((fp=fopen("tobetrans.txt","rb"))==NULL)
        printf("Open file tobetrans.txt error!\n");
    if((fw=fopen("codefile.txt","wb+"))==NULL)
        printf("Open file codefile.txt error!\n");
    char temp;
    fscanf(fp,"%c",&temp);    //从文件读入第一个字符
    while(!feof(fp))
    {
        for(i=1; i<=n; i++)
            if(HT[i].ch==temp) break;    //在赫夫曼树中查找字符所在的位置
        for(r=0; HC[i][r]!='\0'; r++) //将字符对应的编码存入文件
            fputc(HC[i][r],fw);
        fscanf(fp,"%c",&temp);        //从文件读入下一个字符

    }
    fclose(fw);
    fclose(fp);
    printf("\n已将文件hfmtree.txt成功编码,并已存入codefile.txt中！\n\n");
}


//将文件codefile中的代码进行译码，结果存入文件textfile中
void Decoding()
{
    FILE *fp,*fw;
    int m,i;
    char *code,*text,*p;

    if(n==0)
        n=Read_tree(HT);//从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数

    if((fp=fopen("codefile.txt","rb"))==NULL)
        printf("Open file codefile.txt error!\n");
    if((fw=fopen("textfile.txt","wb+"))==NULL)
        printf("Open file textfile.txt error!\n");
    code=(char *)malloc(sizeof(char));
    fscanf(fp,"%c",code);        //从文件读入一个字符
    for(i=1; !feof(fp); i++)
    {
        code=(char *)realloc(code,(i+1)*sizeof(char));   //增加空间
        fscanf(fp,"%c",&code[i]);     //从文件读入下一个字符
    }
    code[i-1]='\0';
// codefile.txt文件中的字符已全部读入，存放在code数组中
    text=(char *)malloc(100*sizeof(char));
    p=text;
    m=2*n-1;
    if(*code=='0')
        find(code,text,HT[m].lchild,m);   //从根节点的左子树去找
    else
        find(code,text,HT[m].rchild,m);   //从根节点的右子树去找

    for(i=0; p[i]!='\0'; i++)  //把译码好的字符存入文件textfile.txt中
        fputc(p[i],fw);

    fclose(fp);
    fclose(fw);

    printf("\n已将codefile.txt文件成功译码，兵已存入textfile.txt文件！\n\n");
}

//将文件codefi1e以紧凑格式显示在终端上,每行50个代码。同时将此字符形式的编码文件写入文件codeprint中。
void Print_code()
{
    FILE *fp,*fw;
    char temp;
    int i;

    if((fp=fopen("codefile.txt","rb"))==NULL)
        printf("Open file codefile.txt error!\n");
    if((fw=fopen("codeprint.txt","wb+"))==NULL)
        printf("Open file codeprint.txt error!\n");

    printf("\n文件codefi1e显示如下:\n");
    fscanf(fp,"%c",&temp);        //从文件读入一个字符
    for (i=1; !feof(fp); i++)
    {
        printf("%c",temp);
        if(i%50==0) printf("\n");
        fputc(temp,fw);   //将该字符存入文件codeprint.txt中
        fscanf(fp,"%c",&temp);        //从文件读入一个字符
    }
    printf("\n\n已将此字符形式的编码写入文件codeprint.txt中！\n\n");

    fclose(fp);
    fclose(fw);

}

//将已在内存中的哈夫曼树显示在屏幕上，并将此字符形式的哈夫曼树写入文件treeprint中。
void Print_tree()
{
    unsigned char T[100][100];
    int i,j,m=0;
    FILE *fp;
    if(n==0)
        n=Read_tree(HT);   //从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数

    Convert_tree(T,0,&m,2*n-1);   //将内存中的赫夫曼树转换成凹凸表形式的树，存于数组T中

    if((fp=fopen("treeprint.txt","wb+"))==NULL)
        printf("Open file treeprint.txt error!\n");
    printf("\n打印已建好的赫夫曼树：\n");
    for(i=1; i<=2*n-1; i++)
    {
        for (j=0; T[i][j]!=0; j++)
        {
            if(T[i][j]==' ')
            {
                printf("    ");
                fputs("    ",fp);
            }
            else
            {
                printf("%d",T[i][j]);
                fprintf(fp,"%d",T[i][j]);
                printf("%c\n",T[i][++j]);
                fprintf(fp,"%c\r\n",T[i][j]);
            }
        }

    }
    fclose(fp);
    printf("\n已将该字符形式的哈夫曼树写入文件treeprint.txt中！\n\n");

}

int main()
{
    char select;

    while(1)
    {
        tips();
        scanf("%c", &select);
        system("cls");
        switch(select)   //选择操作，根据不同的序号选择不同的操作
        {

        case '1':
            Init();
            break;

        case '2':
            Coding();
            break;

        case '3':
            Decoding();
            break;

        case '4':
            Print_code();
            break;

        case '5':
            Print_tree();
            break;

        case '0':
            return 0;
            break;

        default :
            printf("Input error!\n");
        }
        getchar();
        printf("\n按任意键返回主菜单\n");
        getchar();
        system("cls");
    }
    return 0;
}

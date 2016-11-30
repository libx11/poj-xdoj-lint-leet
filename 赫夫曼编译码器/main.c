#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����շ��������Ľṹ��
typedef struct
{
    char ch;                //����һ���򣬴�Ÿýڵ���ַ�
    int weight;
    int parent,lchild,rchild;
} HTNode,*HuffmanTree;
typedef char **HuffmanCode;   //ָ��շ��������ָ��

HuffmanTree HT;    //ȫ�ֱ���
int n=0;    //ȫ�ֱ�������źշ�����Ҷ�ӽ�����Ŀ

void tips()   //����ѡ�����
{
    printf(" |---------------------------------------------------|\n");
    printf(" |--                     ��ѡ�����                --|\n");
    printf(" |---------------------------------------------------|\n");
    printf(" |                                                   |\n");
    printf(" |-------------------1 ��ʼ���շ����� ---------------|\n");
    printf(" |-------------------2      ����      ---------------|\n");
    printf(" |-------------------3      ����      ---------------|\n");
    printf(" |-------------------4  ��ӡ�����ļ�  ---------------|\n");
    printf(" |-------------------5  ��ӡ�շ�����  ---------------|\n");
    printf(" |-------------------0      �˳�      ---------------|\n");
    printf(" |---------------------------------------------------|\n");
}

//��HT[1]��HT[j]��ѡ��parentΪ0��weight��С��������㣬��x��y���������
void select(int j,int *x,int *y)
{
    int i;
//����weight��С�Ľ��
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
//����weight��С�Ľ��
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

//�����շ��������㷨
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

void Convert_tree(unsigned char T[100][100],int s,int *i,int j)//���ļ��еĺշ�����ת���ɰ������ʽ�ĺշ�������ӡ����
{
    int k,l;
    if(HT[j].rchild)//���ϱ�һ������������ҵĽڵ㣬�ʲ�����������������ǵݹ�����ҽڵ�
        Convert_tree(T,s+1,i,HT[j].rchild);

    l=++(*i);       //��ȡ�ڵ����ݲ���������
    for(k=0; k<s; k++)
        T[l][k]=' ';
    T[l][k]=HT[j].weight;
    if(HT[j].rchild)//���ӽڵ���ں�����һ���ַ��Ա�۲�
        T[l][++k]='<';
    else
        T[l][++k]=' ';
    T[l][++k]=0;


    if(HT[j].lchild)//�ݹ������ڵ�
        Convert_tree(T,s+1,i,HT[j].lchild);

}

//���ļ�hfmtree.txt�ж���շ�����������Ҷ�ӽڵ���
int Read_tree()
{
    FILE *fp;
    int i,n;
    HT=(HuffmanTree)malloc(sizeof(HTNode));
    if((fp=fopen("hfmtree.txt","r"))==NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i=1; !feof(fp); i++)
    {
        HT=(HuffmanTree)realloc(HT,(i+1)*sizeof(HTNode));   //���ӿռ�
        fread(&HT[i],sizeof(HTNode),1,fp);   //����һ���ڵ���Ϣ
    }
    fclose(fp);
    n=(i-1)/2;
    return n;
}

//����ʱ����01�ַ���Ѱ����ӦҶ�ӽڵ�ĵݹ��㷨
void find(char *code,char *text,int i,int m)
{

    if(*code!='\0')    //������δ����
    {
        code++;
        if(HT[i].lchild==0&&HT[i].rchild==0)   //���ҵ�Ҷ�ӽڵ�
        {

            *text=HT[i].ch;   //��Ҷ�ӽڵ���ַ�����text��

            text++;
            if((*code=='0'))
                find(code,text,HT[m].lchild,m);    //�Ӹ��ڵ����������
            else
                find(code,text,HT[m].rchild,m);    //�Ӹ��ڵ����������
        }
        else   //�������Ҷ�ӽڵ�
            if(*code=='0')
                find(code,text,HT[i].lchild,m);   //�Ӹýڵ��������ȥ��
            else
                find(code,text,HT[i].rchild,m);   //�Ӹýڵ��������ȥ��
    }
    else
        *text='\0'; //�������

}

//��ʼ������������n���ַ������Ӧ��Ȩֵ������Ȩֵ������������������������ļ�hfmtree��
void Init()
{
    FILE *fp;
    int i,n,w[52];    //�������ַ���Ȩֵ
    char character[52];    //���n���ַ�
    printf("\n�����ַ����� n:\n");
    scanf("%d",&n);        //�����ַ�����С
    printf("����%d���ַ������Ӧ��Ȩֵ:\n",n);
    for (i=0; i<n; i++)
    {
        scanf(" %c",&character[i]);
        scanf("%d",&w[i]);           //����n���ַ��Ͷ�Ӧ��Ȩֵ
    }
    HuffmanCoding(character,w,n);    //�����շ�����

    if((fp=fopen("hfmtree.txt","w"))==NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i=1; i<=2*n-1; i++)
    {
        if(fwrite(&HT[i],sizeof(HTNode),1,fp)!=1)   //�������ĺշ����������ļ�hfmtree.txt��
            printf("File write error!\n");
    }
    printf("\n�շ����������ɹ������Ѵ����ļ�hfmtree.txt��\n");
    fclose(fp);
}

//���ļ�tobetrans�е����Ľ��б��룬Ȼ�󽫽�������ļ�codefile��
void Coding()
{
    FILE *fp,*fw;
    int i,f,c,r, start;
    char *cd;
    HuffmanCode HC;
    if(n==0)
        n=Read_tree(HT);//���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����

//��շ������и�Ҷ�ӽڵ���ַ���Ӧ�ĵı��룬������HCָ��Ŀռ���
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
    fscanf(fp,"%c",&temp);    //���ļ������һ���ַ�
    while(!feof(fp))
    {
        for(i=1; i<=n; i++)
            if(HT[i].ch==temp) break;    //�ںշ������в����ַ����ڵ�λ��
        for(r=0; HC[i][r]!='\0'; r++) //���ַ���Ӧ�ı�������ļ�
            fputc(HC[i][r],fw);
        fscanf(fp,"%c",&temp);        //���ļ�������һ���ַ�

    }
    fclose(fw);
    fclose(fp);
    printf("\n�ѽ��ļ�hfmtree.txt�ɹ�����,���Ѵ���codefile.txt�У�\n\n");
}


//���ļ�codefile�еĴ���������룬��������ļ�textfile��
void Decoding()
{
    FILE *fp,*fw;
    int m,i;
    char *code,*text,*p;

    if(n==0)
        n=Read_tree(HT);//���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����

    if((fp=fopen("codefile.txt","rb"))==NULL)
        printf("Open file codefile.txt error!\n");
    if((fw=fopen("textfile.txt","wb+"))==NULL)
        printf("Open file textfile.txt error!\n");
    code=(char *)malloc(sizeof(char));
    fscanf(fp,"%c",code);        //���ļ�����һ���ַ�
    for(i=1; !feof(fp); i++)
    {
        code=(char *)realloc(code,(i+1)*sizeof(char));   //���ӿռ�
        fscanf(fp,"%c",&code[i]);     //���ļ�������һ���ַ�
    }
    code[i-1]='\0';
// codefile.txt�ļ��е��ַ���ȫ�����룬�����code������
    text=(char *)malloc(100*sizeof(char));
    p=text;
    m=2*n-1;
    if(*code=='0')
        find(code,text,HT[m].lchild,m);   //�Ӹ��ڵ��������ȥ��
    else
        find(code,text,HT[m].rchild,m);   //�Ӹ��ڵ��������ȥ��

    for(i=0; p[i]!='\0'; i++)  //������õ��ַ������ļ�textfile.txt��
        fputc(p[i],fw);

    fclose(fp);
    fclose(fw);

    printf("\n�ѽ�codefile.txt�ļ��ɹ����룬���Ѵ���textfile.txt�ļ���\n\n");
}

//���ļ�codefi1e�Խ��ո�ʽ��ʾ���ն���,ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�codeprint�С�
void Print_code()
{
    FILE *fp,*fw;
    char temp;
    int i;

    if((fp=fopen("codefile.txt","rb"))==NULL)
        printf("Open file codefile.txt error!\n");
    if((fw=fopen("codeprint.txt","wb+"))==NULL)
        printf("Open file codeprint.txt error!\n");

    printf("\n�ļ�codefi1e��ʾ����:\n");
    fscanf(fp,"%c",&temp);        //���ļ�����һ���ַ�
    for (i=1; !feof(fp); i++)
    {
        printf("%c",temp);
        if(i%50==0) printf("\n");
        fputc(temp,fw);   //�����ַ������ļ�codeprint.txt��
        fscanf(fp,"%c",&temp);        //���ļ�����һ���ַ�
    }
    printf("\n\n�ѽ����ַ���ʽ�ı���д���ļ�codeprint.txt�У�\n\n");

    fclose(fp);
    fclose(fw);

}

//�������ڴ��еĹ���������ʾ����Ļ�ϣ��������ַ���ʽ�Ĺ�������д���ļ�treeprint�С�
void Print_tree()
{
    unsigned char T[100][100];
    int i,j,m=0;
    FILE *fp;
    if(n==0)
        n=Read_tree(HT);   //���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����

    Convert_tree(T,0,&m,2*n-1);   //���ڴ��еĺշ�����ת���ɰ�͹����ʽ��������������T��

    if((fp=fopen("treeprint.txt","wb+"))==NULL)
        printf("Open file treeprint.txt error!\n");
    printf("\n��ӡ�ѽ��õĺշ�������\n");
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
    printf("\n�ѽ����ַ���ʽ�Ĺ�������д���ļ�treeprint.txt�У�\n\n");

}

int main()
{
    char select;

    while(1)
    {
        tips();
        scanf("%c", &select);
        system("cls");
        switch(select)   //ѡ����������ݲ�ͬ�����ѡ��ͬ�Ĳ���
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
        printf("\n��������������˵�\n");
        getchar();
        system("cls");
    }
    return 0;
}

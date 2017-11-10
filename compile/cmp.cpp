#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;

#define al 10  // ��ʶ����󳤶�
#define norw 11 //�����ֵ�����
#define txmax 100 //��ʶ����ĳ���
#define nmax 14 //����������λ��
#define amax 2047 //Ѱַ�ռ�
#define levmax 3 //��������Ƕ�ײ���
#define cxmax 2000 //Ŀ���������ĳ���

#define nul 0x1  //��
#define ident 0x2 //��ʶ��
#define number 0x4  //��ֵ
#define plus 0x8  //+
#define minus 0x10 //-
#define times 0x20 //*
#define slash 0x40 // /
#define oddsym 0x80 //�����ж�
#define eql 0x100 // = 
#define neq 0x200 // <>
#define lss 0x400  // <
#define leq 0x800 // <=
#define gtr 0x1000 // >
#define geq 0x2000 // >=
#define lparen 0x4000 // (
#define rparen 0x8000  // )
#define comma 0x10000  // ,
#define semicolon 0x20000 // ;
#define period 0x40000 
#define becomes 0x80000
#define beginsym 0x100000
#define endsym 0x200000
#define ifsym 0x400000
#define thensym 0x800000
#define whilesym 0x1000000
#define dosym 0x2000000
#define callsym 0x4000000
#define constsym 0x8000000
#define varsym 0x10000000
#define prosym 0x20000000

enum object // ���ֱ�ʶ��������
{
    constant, variable, proc
};

enum fct // fct ��ʶ�� pcode �ĸ���ָ��
{
    lit, opr,lod,sto,cal,Int,jmp,jpc
};

typedef struct
{
    enum fct f;
    long l;
    long a;
}instruction;

char infilename[256];
FILE* infile;

char word[norw][al+1];//�����ֱ�
long cc; //�л���������ָ��
long ll; //�л������ĳ���
char ch; //���ڴʷ���������������һ��ȡ�����ַ�
char line[81]; // �л����������ڴ��ļ�����һ�У����ʷ�������ȡ����ʱ֮�� 
long kk; // �ʷ�������
char a[al + 1]; //��ʱ��Ŵʷ����������ڷ����Ĵ�
char id[al + 1]; //�ʷ�������������һ�η��������Ĵ�
unsigned long sym; // �ʷ���������������������һ��ʶ�������token������
unsigned long wsym[norw];//�����ֱ���ÿһ�������ֶ�Ӧ��symbol����
unsigned long ssym[256];//һЩ���Ŷ�Ӧ��symbol���ͱ�
long num; // ������һ��ʶ��������ֵ�ֵ
instruction code[cxmax+1]; //���ɶ�����pcode�������ű���õ�����pcode����

char mnemonic[8][3+1];
unsigned long declbegsys, statbegsys,facbegsys; //������ʼ�����ʽ��ʼ���ʼ���ż�

// ��ȡ��һ���ַ�
void getch(){
    if(cc==ll)
    {
        if(feof(infile))//��ʾ��һ�ο�ʼ��ȡ������һ���Ѿ�����һ�У��Ǿ��ٶ�һ��
        {
            printf("*******************************\n");
            printf(" program incomplete.");
            printf("*******************************\n");
            exit(1);
        }
       
        ll = cc = 0;    
       
        while((!feof(infile)) && ((ch = getc(infile))!='\n')) //�ж��Ƿ�Ϊ�ļ���β������һ�еĽ�β
        {
            printf("%c",ch);
            ll++;
            line[ll] = ch;
        }

        printf("\n");
        ll++;
        line[ll] = ' ';
    }

    //���ǰһ�ζ�ȡ��һ�л��ڽ��дʷ���������ôһ��һ���ַ���ȡ
    cc++;
    ch = line[cc];
}
void getsym(){
    long i, j, k;
    while(ch == ' ' || ch == '\t') //�ȶ�ȡһ��
    {
        getch();
    }   
    if(isalpha(ch)){ // �ж��Ƿ�Ϊ��ĸ
        k = 0; // ���ڼ�¼��ǰtoken�ĳ���
        do {
            if(k < al) // ȷ�� token С�ڱ�ʶ����󳤶�
            {
                a[k] = ch;
                k++;
            }
            getch();
        }while(isalpha(ch)||isalnum(ch));

        //����β��������ֽ�, �óɿ�
        if (k >= kk) {
            kk = k;
        }else{
            do{
                kk--;
                a[kk] = ' ';
            }while(k < kk);
        }

        strcpy(id, a); // id ��ŵ�ǰ�����Ĵ�
        i = 0;
        j = norw - 1;

        do {
            k = (i+j)/2;
            if(strcmp(id, word[k]) <= 0)
            {
                j = k - 1;
            }
            if(strcmp(id, word[k]) >= 0)
            {
                i = k + 1;
            }
        }while(i <= j);

        if(i-1 > j)
        {
            sym = wsym[k];
        }else{
            sym = ident;
        }
    }
}
int main(){
    printf("File name: ");
    scanf("%s",infilename);
    printf("\n");
   
    if((infile=fopen(infilename,"r"))==NULL)
    {
        printf("File %s can't be opened.\n", infilename);
        exit(1);
    }
    cc = 0;
//    cx=0;
    ll = 0;
    ch = ' '; //��ʼ�� ch Ϊ�˵�һ�ζ�ȡ
    kk = al;
    getsym();
    return 0;
}

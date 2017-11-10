#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;

#define al 10  // 标识符最大长度
#define norw 11 //保留字的数量
#define txmax 100 //标识符表的长度
#define nmax 14 //数字允许的最长位数
#define amax 2047 //寻址空间
#define levmax 3 //最大允许的嵌套层数
#define cxmax 2000 //目标代码数组的长度

#define nul 0x1  //空
#define ident 0x2 //标识符
#define number 0x4  //数值
#define plus 0x8  //+
#define minus 0x10 //-
#define times 0x20 //*
#define slash 0x40 // /
#define oddsym 0x80 //奇数判断
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

enum object // 三种标识符的类型
{
    constant, variable, proc
};

enum fct // fct 标识类 pcode 的各条指令
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

char word[norw][al+1];//保留字表
long cc; //行缓冲区的列指针
long ll; //行缓冲区的长度
char ch; //用于词法分析器，存放最近一次取出的字符
char line[81]; // 行缓冲区，用于从文件读出一行，供词法分析获取单词时之用 
long kk; // 词法分析器
char a[al + 1]; //临时存放词法分析器正在分析的词
char id[al + 1]; //词法分析器存放最近一次分析出来的词
unsigned long sym; // 词法分析器输出结果，存放最近一次识别出来的token的类型
unsigned long wsym[norw];//保留字表中每一个保留字对应的symbol类型
unsigned long ssym[256];//一些符号对应的symbol类型表
long num; // 存放最近一次识别出的数字的值
instruction code[cxmax+1]; //生成订单类pcode代码表，存放编译得到的类pcode代码

char mnemonic[8][3+1];
unsigned long declbegsys, statbegsys,facbegsys; //声明开始，表达式开始和项开始符号集

// 读取下一个字符
void getch(){
    if(cc==ll)
    {
        if(feof(infile))//表示第一次开始读取或者上一次已经读完一行，那就再读一行
        {
            printf("*******************************\n");
            printf(" program incomplete.");
            printf("*******************************\n");
            exit(1);
        }
       
        ll = cc = 0;    
       
        while((!feof(infile)) && ((ch = getc(infile))!='\n')) //判断是否为文件结尾或者是一行的结尾
        {
            printf("%c",ch);
            ll++;
            line[ll] = ch;
        }

        printf("\n");
        ll++;
        line[ll] = ' ';
    }

    //如果前一次读取的一行还在进行词法分析，那么一个一个字符读取
    cc++;
    ch = line[cc];
}
void getsym(){
    long i, j, k;
    while(ch == ' ' || ch == '\t') //先读取一行
    {
        getch();
    }   
    if(isalpha(ch)){ // 判断是否为字母
        k = 0; // 用于记录当前token的长度
        do {
            if(k < al) // 确保 token 小于标识符最大长度
            {
                a[k] = ch;
                k++;
            }
            getch();
        }while(isalpha(ch)||isalnum(ch));

        //处理尾部多余的字节, 置成空
        if (k >= kk) {
            kk = k;
        }else{
            do{
                kk--;
                a[kk] = ' ';
            }while(k < kk);
        }

        strcpy(id, a); // id 存放当前分析的词
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
    ch = ' '; //初始化 ch 为了第一次读取
    kk = al;
    getsym();
    return 0;
}

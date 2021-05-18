#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _KEY_WORD_END "waiting for you expanding"   /*定义关键字结束标志*/

using namespace std;

typedef struct  /*单词二元组*/
{
    int categoryCode;/*单词种别码*/
    char *value;    /*单词自身的值*/
}WORD;

char inputBuffer[10000];    //输入缓存区
char wordBuffer[1000] = ""; //单词缓存区
int inputBufferIndex;   //输入缓存区下标
int wordBufferIndex;    //单词缓存区下标

char ch;    //当前读入字符
char *rwtab[] = {"begin","void","int","char","main","if","scanf","printf","while","for","return","end",_KEY_WORD_END};
    //关键词数组

WORD* scanner();    //词法分析函数，获得一个单词
char getChar(); //字符读取函数，从输入缓存区读取一个字符
void removeBlankSymbol();   //去掉空格和\t函数
void concatWord();  //拼接单词函数
int isLetter(); //判断是否是字母函数
int isDigit();  //判断是否是数字函数
int retriveKeyword();   //检索关键字数组函数，在字符数组rwtab中检索
void retractChar(); //回退字符函数，回退一个字符
char* digitToBinary();  //十进制转二进制函数
char* changeWordFormation();    //更改单词的输出形式函数

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int over = 1;
    inputBufferIndex = 0;
    WORD *oneWord = new WORD;

    scanf("%[^#]s",inputBuffer);
    printf("Your words:\n\n");
    printf("---------------------------------\n");
    printf("%s\n",inputBuffer);

    printf("-------------------------------\n\n");
    printf("The result of lexical analyzer:\n\n");
    while(over < 1000){
        oneWord = scanner();
        if(oneWord -> categoryCode <1000){
            printf("(%d,%s)\n",oneWord -> categoryCode,oneWord -> value);
        }
        over = oneWord -> categoryCode;
    }
}


 
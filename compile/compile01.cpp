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
    freopen("input.txt","r",stdin);    // 从input.txt获取输入
    freopen("output.txt","w",stdout);  // 输出到output.txt里

	int over = 1;                            // 判断是否出现#
	inputBufferIndex = 0;                    // 初始化输入缓冲区下标
	WORD *oneWord = new WORD;                // 关键字数组

	scanf("%[^#]s", inputBuffer);            // 读入源程序字符串到缓冲区，以#结束，允许多行输入，#不读入
	printf("Your words:\n\n");
	printf("-------------------------------\n");
	printf("%s\n", inputBuffer);

    printf("-------------------------------\n\n");
    printf("The result of lexical analyzer:\n\n");
	while (over < 1000)                      // 分析源程序直到出现结束符#
	{
		oneWord = scanner();                  // 获得一个新单词
		if (oneWord -> categoryCode < 1000)  // 本程序的种别码数量最多不超过1000个
		{
			printf("(%d,%s)\n", oneWord -> categoryCode, oneWord -> value);
			                                 // 打印种别码和单词自身的值
		}
		over = oneWord -> categoryCode;
	}
}


/*获取一个单词*/
WORD* scanner()
{
    WORD *myWord = new WORD;
    myWord -> categoryCode = 13;
    myWord -> value = "";

    wordBufferIndex = 0;
    getChar();           // 从输入缓冲区读取一个字符到ch中
    removeBlankSymbol(); // 去掉空格

    if(isLetter()) // 如果单词的第一个字符为字母，则说明该单词为变量
    {
        while(isLetter() || isDigit()) // 变量名可以有数字
        {
            concatWord(); // 拼接单词
            getChar();    // 从输入缓冲区读取下一个字符到ch中
        }
        retractChar(); // 回退一个字符
        if((myWord -> categoryCode = retriveKeyword()) == 13) // 说明不是关键字，需要加上引号后输出
        {
            myWord -> value = changeWordFormation();
        }
        else
        {
            myWord -> value = wordBuffer;
        }
        return myWord;
    }
    else if(isDigit()) // 如果单词的第一个字符为数字，则说明该单词为数字
    {
        while(isDigit())
        {
            concatWord(); // 拼接单词
            getChar();    // 从输入缓冲区读取下一个字符到ch中
        }
        retractChar(); // 回退一个字符
        myWord -> categoryCode = 14;
        myWord -> value = digitToBinary(); // 将数字转换成二进制数
        return myWord;
    }
    else // 说明单词为符号
    {
        switch(ch)
        {
            case '+': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“+=”符号
                      {
                         myWord -> categoryCode = 43;
                         myWord -> value = "+=";
                         return myWord;
                      }
                      else if(ch == '+') // 是则说明是“++”符号
                      {
                         myWord -> categoryCode = 26;
                         myWord -> value = "++";
                         return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 21;
                      myWord -> value = "+";
                      return myWord;
                      break;
            case '-': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“-=”符号
                      {
                         myWord -> categoryCode = 44;
                         myWord -> value = "-=";
                         return myWord;
                      }
                      else if(ch == '-') // 是则说明是“--”符号
                      {
                         myWord -> categoryCode = 27;
                         myWord -> value = "--";
                         return myWord;
                      }
                      else if(ch == '>') // 是则说明是“->”符号
                      {
                          myWord -> categoryCode = 54;
                          myWord -> value = "->";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 22;
                      myWord -> value = "-";
                      return myWord;
                      break;
            case '*': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“*=”符号
                      {
                         myWord -> categoryCode = 45;
                         myWord -> value = "*=";
                         return myWord;
                      }
                      else if(ch == '/') // 是则说明是“*/”注释符号
                      {
                          myWord -> categoryCode = 69;
                          myWord -> value = "*/";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 23;
                      myWord -> value = "*";
                      return myWord;
                      break;
            case '/': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“/=”符号
                      {
                         myWord -> categoryCode = 46;
                         myWord -> value = "/=";
                         return myWord;
                      }
                      else if(ch == '/') // 是则说明是“//”注释符号
                      {
                          while(getChar())
                          {
                              if(ch == '\n')
                              {
                                  retractChar(); // 回退一个字符
                                  break;
                              }
                          }
                          myWord -> categoryCode = 67;
                          myWord -> value = "//";
                          return myWord;
                      }
                      else if(ch == '*') // 是则说明是“/*”注释符号
                      {
                          while(getChar())
                          {
                              if(ch == '*')
                              {
                                  getChar();
                                  if(ch == '/')
                                  {
                                      retractChar(); // 回退一个字符
                                      retractChar(); // 回退一个字符
                                      break;
                                  }
                              }
                          }
                          myWord -> categoryCode = 68;
                          myWord -> value = "/*";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 24;
                      myWord -> value = "/";
                      return myWord;
                      break;
            case '%': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“%=”符号
                      {
                         myWord -> categoryCode = 47;
                         myWord -> value = "%=";
                         return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 25;
                      myWord -> value = "%";
                      return myWord;
                      break;
            case '=': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“==”符号
                      {
                         myWord -> categoryCode = 28;
                         myWord -> value = "==";
                         return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 42;
                      myWord -> value = "=";
                      return myWord;
                      break;
            case '>': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“>=”符号
                      {
                          myWord -> categoryCode = 32;
                          myWord -> value = ">=";
                          return myWord;
                      }
                      else if(ch == '>') // 是则说明是“>>”符号
                      {
                          getChar(); // 再获取一个字符
                          if(ch == '=') // 是则说明是“>>=”符号
                          {
                                myWord -> categoryCode = 48;
                                myWord -> value = ">>=";
                                return myWord;
                          }
                          retractChar(); // 回退一个字符
                          myWord -> categoryCode = 40;
                          myWord -> value = ">>";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 30;
                      myWord -> value = ">";
                      return myWord;
                      break;
            case '<': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“<=”符号
                      {
                          myWord -> categoryCode = 33;
                          myWord -> value = "<=";
                          return myWord;
                      }
                      else if(ch == '<') // 是则说明是“<<”符号
                      {
                          getChar(); // 再获取一个字符
                          if(ch == '=') // 是则说明是“<<=”符号
                          {
                                myWord -> categoryCode = 49;
                                myWord -> value = "<<=";
                                return myWord;
                          }
                          retractChar(); // 回退一个字符
                          myWord -> categoryCode = 41;
                          myWord -> value = "<<";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 31;
                      myWord -> value = "<";
                      return myWord;
                      break;
            case '!': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“!=”符号
                      {
                          myWord -> categoryCode = 29;
                          myWord -> value = "!=";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 36;
                      myWord -> value = "!";
                      return myWord;
                      break;
            case '^': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“^=”符号
                      {
                          myWord -> categoryCode = 52;
                          myWord -> value = "^=";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 39;
                      myWord -> value = "^";
                      return myWord;
                      break;
            case '&': getChar(); // 再读入一个&字符
                      if(ch == '=') // 是则说明是“&=”符号
                      {
                          myWord -> categoryCode = 50;
                          myWord -> value = "&=";
                          return myWord;
                      }
                      else if(ch == '&') // 是则说明是“&&”符号
                      {
                          myWord -> categoryCode = 34;
                          myWord -> value = "&&";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 37;
                      myWord -> value = "&";
                      return myWord;
                      break;
            case '|': getChar(); // 再获取一个字符
                      if(ch == '=') // 是则说明是“|=”符号
                      {
                          myWord -> categoryCode = 51;
                          myWord -> value = "|=";
                          return myWord;
                      }
                      else if(ch == '|') // 是则说明是“||”符号
                      {
                          myWord -> categoryCode = 35;
                          myWord -> value = "||";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 38;
                      myWord -> value = "|";
                      return myWord;
                      break;
            case '.': myWord -> categoryCode = 53;
                      myWord -> value = ".";
                      return myWord;
                      break;
            case '\\':getChar(); // 再获取一个字符
                      if(ch == '\\') // 是则说明是“\”转义符号
                      {
                          myWord -> categoryCode = 55;
                          myWord -> value = "\\";
                          return myWord;
                      }
                      else if(ch == 'n')
                      {
                          myWord -> categoryCode = 20; // 换行符
                          myWord -> value = "\\n";
                          return myWord;
                      }
                      retractChar(); // 回退一个字符
                      myWord -> categoryCode = 55;
                      myWord -> value = "\\";
                      return myWord;
                      break;
            case '(': myWord -> categoryCode = 56;
                      myWord -> value = "(";
                      return myWord;
                      break;
            case ')': myWord -> categoryCode = 57;
                      myWord -> value = ")";
                      return myWord;
                      break;
            case '[': myWord -> categoryCode = 58;
                      myWord -> value = "[";
                      return myWord;
                      break;
            case ']': myWord -> categoryCode = 59;
                      myWord -> value = "]";
                      return myWord;
                      break;
            case '{': myWord -> categoryCode = 60;
                      myWord -> value = "{";
                      return myWord;
                      break;
            case '}': myWord -> categoryCode = 61;
                      myWord -> value = "}";
                      return myWord;
                      break;
            case ':': myWord -> categoryCode = 62;
                      myWord -> value = ":";
                      return myWord;
                      break;
            case ',': myWord -> categoryCode = 63;
                      myWord -> value = ",";
                      return myWord;
                      break;
            case ';': myWord -> categoryCode = 64;
                      myWord -> value = ";";
                      return myWord;
                      break;
            case '\'':myWord -> categoryCode = 65;
                      myWord -> value = "\'";
                      return myWord;
                      break;
            case '"': myWord -> categoryCode = 66;
                      myWord -> value = "\"";
                      return myWord;
                      break;
            case 10:  myWord -> categoryCode = 20; // 换行符
                      myWord -> value = "\\n";
                      return myWord;
                      break;
            case '\0':myWord -> categoryCode = 1000; // 此处即到了用户输入的#
                      myWord -> value = "OVER";
                      return myWord;
                      break;
            default:  myWord -> categoryCode = -1;
                      concatWord(); // 拼接单词
                      changeWordFormation(); // 改变单词输出形式
                      char reportError[] = " does not exist in this lexical system";
                      for(int i = 0; reportError[i] != '\0' ; ++ i)
                      {
                            wordBuffer[wordBufferIndex ++] = reportError[i];
                      }
                      wordBuffer[wordBufferIndex] = '\0';
                      myWord -> value = wordBuffer;
                      return myWord;
        }
    }
}

/*从输入缓冲区读取一个字符到ch中*/
char getChar()
{
    ch = inputBuffer[inputBufferIndex];
    ++ inputBufferIndex;
    return ch;
}

/*去掉空格和\t*/
void removeBlankSymbol()
{
    while(ch == ' ' || ch == '\t')
    {
        ch = inputBuffer[inputBufferIndex];
        ++ inputBufferIndex;
    }
}

/*拼接单词*/
void concatWord()
{
    wordBuffer[wordBufferIndex] = ch;
    ++ wordBufferIndex;
    wordBuffer[wordBufferIndex] = '\0';
}

/*判断是否字母*/
int isLetter()
{
    if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_') // 变量名可以有下划线
    {
        return 1;
    }
    return 0;
}

/*判断是否数字*/
int isDigit()
{
    if(ch >= '0' && ch <= '9')
    {
        return 1;
    }
    return 0;
}

/*检索关键字数组*/
int retriveKeyword()
{
    int i = 0;
    while(strcmp(rwtab[i], _KEY_WORD_END))
    {
        if(!strcmp(rwtab[i], wordBuffer)) // 相等时strcmp函数返回0，相等于false
        {
            return i + 1;
        }
        ++ i;
    }
    return 13;
}

/*回退一个字符*/
void retractChar()
{
    -- inputBufferIndex;
}

/*将十进制转换成二进制*/
char* digitToBinary()
{
    // 在<stdlib.h>头文件中有两个函数int atoi(char *p)和char *itoa(int value, char *string, int radix)；
    // 前者将装有整数的char数组转化为整数，后者将整数按位数分解依次存入char数组中。
    itoa(atoi(wordBuffer), wordBuffer, 2);
    return wordBuffer;
}

/*更改单词的输出形式，让自定义变量或无法识别的单词能以'单词名'的形式输出，与关键字作区分*/
char* changeWordFormation()
{
    for(int i = wordBufferIndex - 1; i >= 0; -- i)
    {
        wordBuffer[i + 1] = wordBuffer[i];
    }
    wordBuffer[0] = '\'';
    wordBuffer[++ wordBufferIndex] = '\'';
    wordBuffer[++ wordBufferIndex] = '\0';
    return wordBuffer;
}


 
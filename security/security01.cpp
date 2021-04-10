#include <stdio.h>
#include <stdlib.h>


char cleartext[10];
int ciphertext[10];
int secret=0;

int caesar(int secret){
    
    printf("请输入明文:");
    scanf("%s",cleartext);
    for(int i=0;i<10;i++){
        int asc_clear=cleartext[i];
        if(asc_clear<97){
            break;
        }
        int center = ((asc_clear+secret)-97)%26;
        int asc_cipher=97+center;
        ciphertext[i]=asc_cipher;
        //printf("%d",ciphertext[i]);
        if(i==0){
            printf("密文是：");
        }
        printf("%c",ciphertext[i]);
    }

    return 0;
}

int main(){
    printf("请输入密钥:");
    scanf("%d",&secret);
    caesar(secret);
    //printf("%s",cleartext);
    //printf("%s",ciphertext);
    printf("\n");
    system("pause");
    return 0;
}
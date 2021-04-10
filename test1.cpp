#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(){
    
    char a[6]={'b'};
    int b[10];
    char c[6];
    for(int i=0;i<6;i++){
        if((a[i])>=97){
            b[i]=a[i];
            c[i]=b[i];
        }
        printf("%d",b[i]);
        printf("%c",c[i]);
    }

    system("pause");
    return 0 ;
}
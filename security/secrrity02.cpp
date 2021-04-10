#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char secret[10];
char cleartext[20];
char ciphertext[20];
int secret_length;

//�ַ�������
// int length(char a[]){
//     int length=0;
//     for(int i=0;i<99;i++){
//         int asc_secret=a[i];
//         if(asc_secret<97){
//             break;
//         }else{
//             length++;
//         }
//     }
//     return length;
// }


//���鳤��
int length_02(int a[]){
    int length=0;
    for(int i=0;i<99;i++){
        if(a[i]==0){
            break;
        }else{
            length++;
        }
    }
    return length;
}

//��Կת��Ϊascll��
int asc[10];
int transform(int length){
    for(int i=0;i<length;i++){
        if(secret[i]>=97){
            asc[i] = secret[i];
            //printf("%d",asc[i]);
        }
    }
    return 0;
}

//��Կ������ĸ�������
int secret_new[10];
void permute(){
    int min,index;
    int asc_length = length_02(asc);
    for(int i=0,k=1;i<asc_length;i++,k++){
        min = asc[i];
        for(int j=0;j<asc_length;j++){
            if(min>asc[j]){
                min = asc[j];
                index = j;
            }else{
                continue;
            }
        }
        if(min==asc[i]){
            asc[i]=123;
            secret_new[i]=k;
        }else{
            asc[index]=123;
            secret_new[index]=k;
        }
    } 
}


//����ת��Ϊ��ά����
int to_clear_array(int secret_length){
    int cleartext_length = strlen(cleartext);
    if(cleartext_length%secret_length!=0){
        int row = (cleartext_length/secret_length)+1;
    }else{
        int row = cleartext_length/secret_length;
    }
    int row = cleartext_length/secret_length;
    int line = secret_length;

    //����ת��Ϊ��ά����
    char clear_array[row][line];
    int k=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<line;j++){
            clear_array[i][j] = cleartext[k];
            k++;
        }
    }

    //����ת��Ϊ���ĵĶ�ά����
    char cipher_array[row][line];
    k=0;
    for(int i=0;i<line;i++){
        int cipher_line = secret_new[k]-1;
        for(int j=0;j<row;j++){
            
            cipher_array[j][i] = clear_array[j][cipher_line];
        }
        k++;
    }

    //�������
    k=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<line;j++){
            if(cipher_array[i][j]==0){
                ciphertext[k] = 32;
                k++;
            }else{
                ciphertext[k] = cipher_array[i][j];
                k++;
            }
        }
    }
    return 0;
}


int main(){

    printf("��������Կ��");
    scanf("%s",secret);

    printf("���������ģ�");
    scanf("%s",cleartext);

    int secret_length = strlen(secret);
    transform(secret_length);
    permute();

    to_clear_array(secret_length);
    printf("�����ǣ�");
    for(int i=0;i<strlen(ciphertext);i++){
        printf("%c",ciphertext[i]);
    }
    printf("\n");

    system("pause");
    return 0;

}
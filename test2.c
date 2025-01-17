#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char const *argv[]){

    long double s = 0;
    int x = 15;
    int m = 0;
  

    char strx[100];
    sprintf(strx, "%d", x);

    int i = 0;
    while(i < strlen(strx)){
        m = m + strx[i] - '0';
        i++;
    }

    int aPrefixInt = m % 9;
    int aSuffixInt = (int) x / 9;

    char aPrefixStr[10];
    sprintf(aPrefixStr, "%d", aPrefixInt);

    char *a;

    char aSuffixStr[aSuffixInt];

    i = 0;
    while(i < aSuffixInt){
        aSuffixStr[i] = '9';
        i++;
    }

    a = strcat(aPrefixStr, aSuffixStr); 
    long double aInt =strtold(a, NULL);

    //printf("%d",aInt);

    char ones[x];
    long double onesInt;

    for(i = 0; i < x; i++){
        ones[i] = '1';
    } 

    onesInt =  strtold(ones, NULL);    

    //printf("%d", onesInt);

    long double k = aInt;
    char strk[x];

    int hasZero;
    int digCount;

    while(k <= onesInt){
        //printf("%d",k);
        hasZero = 0;
        digCount = 0;

        sprintf(strk, "%.Lf", k);
        
        
        for(i = 0; i < strlen(strk); i++){
            if(strk[i] == '0'){
                hasZero = 1;
                break;
            }
            digCount += strk[i] - '0';
        }
        if(hasZero == 0 && digCount == x){
            //printf("%s ",strk);
            s+=k;
        }
        k+=9;
    }

    printf("%.Lf\n", s);

}
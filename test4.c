#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char charAdd(char c, int i){
    int x;
    x = i + c - '0';
    char f[1];
    sprintf(f, "%d", x);
    return f[0];
}

int main(int argc, char const *argv[])
{

    long double sum = 0;
    int x = 10;
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

    sum+=aInt;

   // printf("%.Lf\n",aInt);

    char ones[x];
    long double onesInt;

    for(i = 0; i < x; i++){
        ones[i] = '1';
    } 

    onesInt =  strtold(ones, NULL);

    char zMult[aSuffixInt];

    for(i = 0; i < aSuffixInt; i++){
        zMult[i] = '0';
    }

    //printf("%s", zMult);
   
    long double adders[1000];

    for(i = 0; i < aSuffixInt; i++){
        zMult[i] = charAdd(zMult[i],9);
        adders[i] = strtold(zMult, NULL);  
        //printf("%.Lf\n", adders[i]);
    }


    long double arr1[1000];
    long double arr2[1000];

    arr1[0] = aInt;
    
    char aRev[100];
    

    char aExp[100];
    char aExp2[100];
    int isExped = 0;


    long double aRevInt;

    for(i = 0; i < strlen(a); i++){
        aExp[i] = a[i];
    }
    
   //printf("%s\n", aExp);

    int counter = 1;
    long double lastElem = 0;

    while(lastElem <= onesInt){

        int j = 0;
        int c = 0;
        int k = 0;
        int sDigit = 0;
        int hasZero = 0;
        int hasRept = 0;
        char arrStr[100];

        for(i = 0; arr1[i] != 0; i++ ){

            for(k = 0; adders[k] != 0; k++){
                // sprintf(arrStr, "%.Lf",arr1[i] + adders[k]);

                // for(j = 0; j<strlen(arrStr);j++){
                //     if(arrStr[j] == '0'){
                //         hasZero = 1;
                //         break;
                //     }
                // }

                // if(hasZero == 1){
                //     break;
                // }

                for(j = 0; arr2[j]!=0;j++){
                    if(arr2[j] == arr1[i] + adders[k]){
                        hasRept = 1;
                    }
                }
                if(hasRept == 0){
                    arr2[c] = arr1[i] + adders[k];
                    c++;
                }
                hasRept = 0;

            }

        }

        for(i = 0; arr2[i]!=0; i++){
            sprintf(arrStr, "%.Lf",arr2[i]);
            sDigit = 0;
            for(j = 0; j<strlen(arrStr);j++){
                    if(arrStr[j] == '0'){
                        hasZero = 1;
                        
                    }
                    sDigit += arrStr[j] - '0';
                }
            if(hasZero == 0 && sDigit == x){
                //printf("%.Lf\n", arr2[i]);
                sum+=arr2[i];
            }
            hasZero = 0;
            arr1[i] = arr2[i];
            lastElem = arr2[i];
        }



        for(i = 0; i < strlen(aExp); i++){
            aExp2[i] = aExp[i];
            aRev[i] = aExp[strlen(aExp)-1-i];
        }

    
        //printf("--%s\n",aRev);
        
        aRevInt = strtold(aRev, NULL);
        //printf("++%.Lf\n",aRevInt);
        int aRevLen = strlen(aExp);
        isExped = 0;
        if(lastElem == aRevInt){
            for(i = 0; i < aRevLen; i++){
                if(aExp[i] != '1' && isExped == 0){
                    aExp[i] = '1';
                    aExp[i+1] = charAdd(aExp2[i],-1);
                    isExped = 1;
                    aRevLen++;
                    i++;
                }
                else{
                    if(aRevLen == strlen(aExp)){
                        aExp[i] = aExp2[i];
                    }
                    else{
                    aExp[i] = aExp2[i-1]; 
                    }
                    
                }
            }
            //printf("--%s\n", aExp);
            
            for(i=0;arr2[i]!=0;i++){
                arr2[i] = 0;
                arr1[i] = 0;
            }
            arr1[0] = strtold(aExp, NULL);
        }
        

        counter++;
        // if(counter == 20){
        //     break;
        // }

    }

    printf("%.Lf", sum);

}


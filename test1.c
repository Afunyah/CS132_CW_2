#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int getInt(const char *iStr){
        
}


char *getStr(){

}

char charAdd(char c, int i){
    int x;
    x = i + c - '0';
    char f[1];
    sprintf(f, "%d", x);
    return f[0];
}

int main(int argc, char const *argv[])
{
    
    int x = 29;
    int m = 0;

    char strx[100];
    sprintf(strx, "%d", x);

    int i = 0;
    while(i < strlen(strx)){
        // printf("%c\n",strx[i]);
        m = m + strx[i] - '0';
        i++;
    }

    // printf("%d", m);

    int aPrefixInt = m % 9;
    int aSuffixInt = (int) x / 9;

    // printf("%d ", aPrefixInt);
    // printf("%d ", aSuffix);

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
    int aInt = (int) strtol(a, NULL, 10);

    // printf("%s\n",a);
    // printf("%d\n",aInt);


    char strMult[aSuffixInt];
    strMult[0] = '0';
    
    i = 1;
    while(i < aSuffixInt){
        strMult[i] = '0';
        i++;
    }

    int strMultInt = (int) strtol(strMult, NULL,10);
    
    // printf("%d\n",strMultInt);

    int nextTerm = strMultInt * 9 + aInt;
    printf("%d\n",nextTerm);

    //printf("%s\n",strMult);
   
    int counter = 1;    
    int n = 3;
    int p;
    int reduce = 0;
    i = 0;

    while(1 == 1){
        p = 0;


        int f = 0;
        int sLength = strlen(strMult); 
        while(p < n){

            for(i = f; i < sLength; i++){
                
                strMult[i] = charAdd(strMult[i], 1);
                printf("%s\n",strMult);
                
                p++;
                //printf("%d",p);
            }
            f=2;
            
            //printf("here");

            // if(strMult[sLength-1] == strMult[sLength-2] && strMult[sLength-1] != '0' && strMult[sLength-1] != strMult[0]){ 
            //    // printf("here");
            //     // strMult[0] = charAdd(strMult[0], -1);
            //     // strMult[sLength-1] = '0';
            //     // strMult[sLength-2] = charAdd(strMult[sLength-2], 1);
            // }

            int k = 1;
            while(k<counter){
                int c = 3 + (2+k);
                //printf("%d",p);
                if(p == c || p == 3){
                    //printf("pp");
                    f = 1;
                    for(i = f+1; i < sLength; i++){
                        strMult[i] = '0';
                    }
                }
                k++;
            }

            if(p == n){
                //strMult[0] = charAdd(strMult[0], 1);
                for(i = 1; i < sLength; i++){
                    strMult[i] = '0';
                    //f = 0;
                }
                //printf("%s\n",strMult);
                //printf("ok");
            }

        }

        n = n + (2 + counter);
        counter++;


        if(counter==5){break;}

    }
        

    return 0;
}

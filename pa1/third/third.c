#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned short x;

int get(int n, int v){
    int ans = 0;
    unsigned short m;

    m = x&(1<<n);
    if(m==0){
        ans = 0;
    }
    else{
        ans = 1;
    }
    return ans;
}
int set(int n,int v){
    if(v==0){
        x= x&(~(1<<n));
    }
    else{
        x=x|(1<<n);
    }
    return x;
}

int main(int argc, char** argv){
    //short variable

    //command
    char command[5];
    int n=0, v=0;

    FILE* fpoint=fopen(argv[1], "r");

    fscanf(fpoint,"%hu", &x);
    while(fscanf(fpoint,"%s %d %d", command, &n, &v)!=EOF){
        //cmp compares strings like .equals in java
        if(strcmp(command,"set")==0){
            x=set(n,v);
            printf("%hu\n", x);
        }
        else if(strcmp(command,"get")==0){
            int ans = get(n, v);
            printf("%d\n", ans);
        }
        else if(strcmp(command,"comp")==0){
            x=x^(1<<n);
            printf("%hu\n", x);
        }
    }

    fclose(fpoint);
    return 0;
}
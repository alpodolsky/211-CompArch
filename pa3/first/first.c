#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int mCount, hCount, i ,j, read=0, write=0;
unsigned long int count;
struct Node** cache;
char *policy;
typedef struct Node{
    unsigned long long int tag;
    int valid;
    unsigned long int time;//?
}Node;
struct Node** createCache(int setNum, int assocN){
    cache = (Node**)malloc(sizeof(Node*)*setNum);
    for (i = 0;i<setNum;i++){
        cache[i]= (Node*)malloc(sizeof(Node)*assocN);
    }
    for(i=0;i<setNum; i++){
        for(j=0; j <assocN; j++){
            cache[i][j].valid = 0;
        }
    }
    return cache;
};

void readM(unsigned long long int tagIndex,unsigned long long int setIndex,int assocN);
void writeM(unsigned long long int tagIndex,unsigned long long int setIndex,int assocN);
void freeMatrix(Node** cache, int setNum, int assocN){
    for(i=0;i<setNum;i++){
        free(cache[i]);
    }
    free(cache);
    return;
};
int main(int argc, char** argv){
    //check if 6 args
    if(argc !=6){
        printf("Error, wrong amount of arguments");
    }
    //first arg cache size
    int cacheSize = atoi(argv[1]);
    if(ceil(log2(cacheSize))!=floor(log2(cacheSize))){
        printf("Error, cachesize not power of 2");
        return 0;
    }

    //second arg is blocksize
    int blockSize = atoi(argv[2]);
    if(ceil(log2(blockSize))!=floor(log2(blockSize))){
        printf("Error, blocksize not power of 2");
        return 0;
    }

    int assocN=0;
    int setNum=0;

    //third arg is policy
    if(strcmp(argv[3], "fifo")!=0 &&strcmp(argv[3],"lru")!=0){
        printf("Error, policy not fifo or lru");
        return 0;
    }
    //sets policy to referenced later
    else if (strcmp(argv[3], "fifo")==0 ||strcmp(argv[3],"lru")==0){
        if(strcmp(argv[3], "fifo")==0){
            policy ="f";
        }
        if(strcmp(argv[3], "lru")==0){
            policy ="l";
        }
    }
    //fourth arg is assoc
    char assoTest[7] = "assoc:";

    //not sure if all edge cases are covered but things like dirt, ausoc and incorrect powers of 2 are noticed
    if(strcmp(argv[4],"direct")!=0&&strcmp(argv[4],"assoc")!=0&&argv[4][5]!=':'){
        printf("Error incorrect associativity");
        return 0;
    }
    else {
        if(strcmp(argv[4], "direct")==0){
            assocN = 1;
            setNum = cacheSize/blockSize;
        }
        else if(strcmp(argv[4], "assoc")==0){
            setNum = 1;
            assocN = cacheSize/blockSize;
        }

        else {
            for(i = 0; i <6;i++){
                if(assoTest[i]!=argv[4][i]){
                    printf("Error incorrect associativity");
                    return 0;
                }
            }
            sscanf(argv[4],"assoc:%d",&assocN);

            if(ceil(log2(assocN))!=floor(log2(assocN))){
                printf("Error, associativity not power of 2");
                return 0;
            }
            else{
                setNum = cacheSize/blockSize/assocN;
            } 
        }
    }
 
    //fifth arg is read file
    FILE* fpoint = fopen(argv[5],"r");
    if(fpoint ==NULL){
        printf("Error with tracefile");
        return 0;
    }

    char letter;
    unsigned long long int address;//llx capture

    //bits for tag, index, offset
    int blockBit =log2(blockSize);
    int setBit= log2(setNum);
    cache = createCache(setNum, assocN);
    unsigned long long int setmask =((1<<setBit)-1);
    unsigned long long int setIndex;
    unsigned long long int tagIndex;


    while(fscanf(fpoint, "%c %llx\n", &letter, &address)){
        setIndex=(address>>blockBit)&setmask;
        tagIndex=address>>(blockBit+setBit);

        if(letter =='#'){
            break;
        }
        if(letter =='W'){
            writeM(tagIndex,setIndex,assocN);
        }
        if(letter =='R'){
            readM(tagIndex,setIndex,assocN);
        }
    }
    freeMatrix(cache, setNum, assocN);
    fclose(fpoint);
    printf("Memory reads: %d\n", read);
    printf("Memory writes: %d\n", write);
    printf("Cache hits: %d\n", hCount);
    printf("Cache misses: %d\n", mCount);
    return 0;
}




void readM(unsigned long long int tagIndex,unsigned long long int setIndex,int assocN){
    int min;
    for(i=0; i<assocN;i++){
        if(cache[setIndex][i].valid==0){
            mCount++;
            read++;
            count++;
            cache[setIndex][i].valid=1;
            cache[setIndex][i].tag=tagIndex;
            cache[setIndex][i].time = count;
            return;
        }
        else{
            if(strcmp(policy, "f")==0&&cache[setIndex][i].tag==tagIndex){
                hCount++;
                return;
            }
            if(strcmp(policy, "l")==0&&cache[setIndex][i].tag==tagIndex){
                hCount++;
                count++;
                cache[setIndex][i].time = count;
                return;
            }
            if(i==(assocN-1)){
                mCount++;
                read++;
                min = 0;
                for(j=0;j<assocN;j++){
                    if(cache[setIndex][j].time<=cache[setIndex][min].time){
                        min=j;
                    }
                }
                cache[setIndex][min].valid=1;
                cache[setIndex][min].tag = tagIndex;
                count++;
                cache[setIndex][min].time=count;
                return;
            }
        }
    }
    return;
}
void writeM(unsigned long long int tagIndex,unsigned long long int setIndex,int assocN){
    int min;
    for(i=0;i<assocN;i++){
        if(cache[setIndex][i].valid==0){
            mCount++;
            read++;
            write++;
            count++;
            cache[setIndex][i].valid=1;
            cache[setIndex][i].tag = tagIndex;
            cache[setIndex][i].time = count;
            return;
        }
        else{
            if(strcmp(policy, "f")==0&&cache[setIndex][i].tag==tagIndex){
                hCount++;
                write++;
                return;
            }

            if(strcmp(policy, "l")==0&&cache[setIndex][i].tag==tagIndex){
                hCount++;
                write++;
                count++;
                cache[setIndex][i].time = count;
                return;
            }
            if(i==(assocN-1)){
                mCount++;
                read++;
                write++;
                min = 0;
                for(j=0;j<assocN;j++){
                    if(cache[setIndex][j].time<=cache[setIndex][min].time){
                        min=j;
                    }
                }
                cache[setIndex][min].valid = 1;
                cache[setIndex][min].tag = tagIndex;
                count++;
                cache[setIndex][min].time=count;
                return;
            }
        }
    }
    return;
}



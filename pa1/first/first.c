#include <stdlib.h>
#include <stdio.h>


void arraySort(int array[], int e, int arrSize){
    int i, j ,temp, arrS= arrSize-1;

    //sort odd
    for(i=0;i<arrSize-e;i++){
        for(j=0;j<arrS-e-i;j++){
            if(array[j]>array[j+1]){
                temp = array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }

    //Sort even
    for(i=arrSize-e;i<arrS;i++){
        for(j=arrSize-e;j<arrS;j++){
            if(array[j]<array[j+1]){
                temp = array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}

//main reads the files correctly
int main(int argc, char** argv) {

    int arrSize=0, i, j ,eCount;

    FILE* fpoint = fopen(argv[1], "r");
    

    fscanf(fpoint, "%d", &arrSize);
    int *array;
    array = (int*)malloc(arrSize*sizeof(int));


    
    for(i = 0; i <arrSize; i++){
        fscanf(fpoint, "%d", &array[i]);
        
        if(abs(array[i]%2)==0){
            eCount++;
        }
    }

    int temp, arrS=arrSize-1;
    
    for(i=0;i<arrS;i++){
        if(abs(array[i]%2)==0){
            for(j=i+1;j<arrS&&abs(array[j]%2)!=1;j++);
            temp = array[i];
            array[i]=array[j];
            array[j]=temp;
        }
    }
    
    fclose(fpoint);
    
    arraySort(array, eCount, arrSize);
    
    for(i = 0; i <arrSize;i++){
        printf("%d\t", array[i]);
    }
    free(array);
    return 0;
}
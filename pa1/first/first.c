#include <stdlib.h>
#include <stdio.h>

//takes in an array, even number count, and arraysize(technically the last index not size)
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

    int arrSize=0, i=0, j=0 ,eCount=0;
    //points to a file and opens it with the 'read' permission
    FILE* fpoint = fopen(argv[1], "r");
    
    //looks for a number and makes that the arraysize
    fscanf(fpoint, "%d", &arrSize);
    int *array;
    //allocate space for the array
    array = (int*)malloc(arrSize*sizeof(int));

    //scans for a number up to the size of the array
        //takes not if the number is even on each iteration
        //can be odd instead, its purpose stays the same
    for(i = 0; i <arrSize; i++){
        fscanf(fpoint, "%d", &array[i]);
        if(abs(array[i]%2)==0){
            eCount++;
        }
    }
    //close the file because we dont need it anymore
    fclose(fpoint);

    int temp, arrS=arrSize-1;
    for(i=0;i<arrS;i++){
        if(abs(array[i]%2)==0){
            //look for the first odd entry in the array and swap them
            for(j=i+1;j<arrS&&abs(array[j]%2)!=1;j++);
            temp = array[i];
            array[i]=array[j];
            array[j]=temp;
        }
    }
    
    //send relevant information to sort function
    arraySort(array, eCount, arrSize);
    //print the results
    for(i = 0; i <arrSize;i++){
        printf("%d\t", array[i]);
    }
    free(array);//free the allocated memory
    return 0;
}
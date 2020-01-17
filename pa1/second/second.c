#include <stdlib.h>
#include <stdio.h>

//the node structure for the linked list
struct Node{
    int val;
    //pointer for next in a node
    struct Node* next;
};
void insert(struct Node **hash, int key, int number){
    //hash[key] is empty
    if(hash[key]==NULL){
        hash[key] = (struct Node*)malloc(sizeof(struct Node));
        hash[key]->val=number;
        hash[key]->next=NULL;
        printf("inserted\n");
        return;        
    }
    //hash[key] is not empty
    else {
        struct Node*temp, *insert;
        //loops thru list until NULL node, checking if current node's value is == number
        for(temp = hash[key]; temp!=NULL;temp =temp->next){
            //if number is present already
            if(temp->val==number){
                printf("duplicate\n");
                return;
            }         
        }
        //just incase it is anything else
        if(temp==NULL){
            insert = (struct Node*)malloc(sizeof(struct Node));
            insert->val = number;
            temp->next=insert;
            insert->next = NULL;          
            printf("inserted\n");
            return;
        } 
        else{
            printf("This should never occur\n");
            return;
        }      
    }
};
void search(struct Node**hash, int key, int number){
    //if number is not present
    if(hash[key]==NULL){
        printf("absent\n");
        return;
    }
    //if key exists
    else if(hash[key]!=NULL){
        struct Node*temp;
        for(temp = hash[key]; temp!=NULL;temp=temp->next){
            if(temp->val==number){ 
                printf("present\n");
                return;
            }                    
        }
        if(temp==NULL){
            printf("absent\n");
            return;
        }  
    }
};
int main(int argc, char** argv){
    //init hash type struct(really array of pointer nodes that will each point to their own LL's)
    struct Node **hash= (struct Node**)malloc(10000*sizeof(struct Node));
    struct Node *start = NULL;

    FILE* fpoint = fopen(argv[1], "r");

    char letter;//used later to indicate command(either insert,'i' or search,'s')
    char letter;
    int number, i;
    //sets all hash values to NULL
    for(i=0;i<10000;i++){
        hash[i]=NULL;
    }
    //loops until end of file

    while(fscanf(fpoint, "%c %d", &letter,&number)!=EOF){
        //hash key is the modded value of number by the hash table size which is 10k in this case
        int key = abs(number%10000);

        if(letter =='i'){
            insert(hash, key, number);
        } 
        
        else if(letter=='s'){
            search(hash, key, number); 
        }
    }
    fclose(fpoint);
    return 0;
}
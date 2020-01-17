#include <stdlib.h>
#include <stdio.h>

//the node structure for the linked list
struct Node{
    int val;
    //pointer for next in a node
    struct Node* next;
};
int main(int argc, char** argv){
    struct Node **hash= (struct Node**)malloc(10000*sizeof(struct Node));
    struct Node *start = NULL;

    FILE* fpoint = fopen(argv[1], "r");

    char letter;
    int number, i;
    //sets all hash values to NULL
    for(i=0;i<10000;i++){
        hash[i]=NULL;
    }
    
    while(fscanf(fpoint, "%c %d", &letter,&number)!=EOF){
        int key = abs(number%10000);
        
        if(letter =='i'){
            //hash[key] is empty

            if(hash[key]==NULL){
                start = (struct Node*)malloc(sizeof(struct Node));
                start->val=number;
                start->next=NULL;
                hash[key]=start;
                printf("inserted\n");
                
            }
            //hash[key] is not empty
            else {
                struct Node*temp, *insert;
                if(hash[key]->next==NULL){
                    if(hash[key]->val==number){
                        printf("duplicate\n");
                    }
                }
                //loops thru list
                for(temp = hash[key]; temp->next!=NULL;temp =temp->next){
                    //if number is present already
                    if(temp->val==number){
                        printf("duplicate\n");
                        break;
                    }
                    
                }
                if(temp->val!=number){
                    insert = (struct Node*)malloc(sizeof(struct Node));
                    insert->val = number;
                    //sets the value that stopped the loop to insert
                    temp->next=insert;
                    insert->next = NULL;
                       
                    printf("inserted\n");
                }
                
            }
        }
        else if(letter=='s'){
            //if number is not present
            if(hash[key]==NULL){
                printf("absent\n");
            }

            //if key exists
            else if(hash[key]!=NULL){
                struct Node*temp;

                
                for(temp = hash[key]; temp!=NULL;temp=temp->next){
                    if(temp->val==number){ 
                        printf("present\n");
                        break;
                    }                    
                }
                if(temp==NULL){
                    printf("absent\n");
                }  
            }
        }
    }
    fclose(fpoint);
    return 0;
}
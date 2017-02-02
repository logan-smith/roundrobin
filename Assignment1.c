#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 50
#define MAX_CANIDATE_TABLE_SIZE 100

typedef struct node{
    char* word;
    struct node* next;
    struct node* prev;
}node;

/*
    burst is how long the process is
    quantum is how long the processor spends on each process before it moves on
    after a quantum is over move onto next available process
    if idle, time does not increase when new process arrives
    add quantum to time per process
    remember that if burst reaches 0 before quantum just add time spent on process to time
*/

void insertNode(node** head, node** tail);
node* startsWithLetter(FILE* input, char firstLetter, node** tail);

int i=0;

int main(int argc,char* argv[]){

    FILE *inputFile = fopen(argv[1], "r");


  /*char fileInput[5000];
    while(fgets(fileInput,5000, inputFile))
        printf("%s",fileInput);
    printf("\n");
    */

    //initialize nodes
    node* tail=NULL;
    node* head=NULL;

    //creates first node
    insertNode(&head, &tail);

    char firstC;
    firstC=fgetc(inputFile);

    while(firstC!=EOF){
        //if letter adds entire word to a node then gets then next char
        if(isalpha(firstC)){
            tail=startsWithLetter(inputFile, firstC, &tail);
            insertNode(&head,&tail);
            firstC=fgetc(inputFile);
        }
        //if number adds entire word to a node then gets then next char
        else if(isdigit(firstC)){
            tail=startsWithLetter(inputFile, firstC, &tail);
            insertNode(&head,&tail);
            firstC=fgetc(inputFile);
        }
         //if symbol adds entire word to a node then gets then next char
        else if(ispunct(firstC)){
            if(firstC!='#'){
                tail=startsWithLetter(inputFile, firstC, &tail);
                insertNode(&head,&tail);
                firstC=fgetc(inputFile);
            }
            else{
              //  firstC=fgetc(inputFile);
                while(firstC!='\n'){
                    firstC=fgetc(inputFile);
                }
            }
        }
        else{
         //if whitespace, prints it out to keep everything in order
            //printf("%c",firstC);
            firstC=fgetc(inputFile);
        }
    }



    //int i=0;
    while(head->next!=NULL){
        printf("%s\n",head->word);
        head=head->next;
    }
    fclose(inputFile);

    return 0;

}



node* startsWithLetter(FILE* input, char firstLetter, node** tail){
    int nextLetter,len=30;
    char* word=calloc(len+1,sizeof(char));
    int i=1;

    word[0]=firstLetter;
    nextLetter=fgetc(input);

    //while next char is letter or number keeps scanning to make char array
    while(isalpha(nextLetter)||isdigit(nextLetter)||ispunct(nextLetter)){
        if(i>=len){
            len*=2;
            word=realloc(word,len+1);
        }

        word[i]=nextLetter;
        i++;
        nextLetter=fgetc(input);
    }

    if (nextLetter != EOF )
        fseek(input, -1, SEEK_CUR);

    //used to print input without comments
    //printf("%s ",word);
    (*tail)->word=word;

    return *tail;
}


void insertNode(node** head, node** tail){
    if(*head==NULL){
        *head=(node*)malloc(sizeof(node));
        (*head)->next=NULL;
        (*head)->prev=NULL;
        *tail=*head;
    }
    else{

        (*tail)->next=(node*)malloc(sizeof(node));
        (*tail)->prev=*tail;
        *tail=(*tail)->next;
        (*tail)->next=NULL;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strings built in functions
#include <stdbool.h> //boolean type and values

struct Edge{
    double dist;//distance
    char target[50];//target city (destination)
};
typedef struct Edge* edge;

struct listNode{
    int num;
    edge e;
    struct listNode* next;
};
typedef struct listNode* list;

struct Node{
    char name[50];//country name (node)
    list adjacenties;//adjacenties with other countries
    struct node* parent;//parent of the node
};
typedef struct Node* node;
node graph;

void insertInGraph(char name[50],list adj,node graph){
    bool exist=false;
    while(graph!=NULL){
        if(strcasecmp(name,graph->name)==0){
            list temp=adj;
            insertInList(graph->adjacenties->e,temp);
            adj=temp;
            exist=true;
        }
    }
    if(exist==false){
        graph=(node)malloc(sizeof(node));
        if(graph==NULL)
            printf("\nOut of memory!");
        else{
            strcpy(graph->name,name);
            makeListEmpty(adj);
            graph->adjacenties=adj;

        }


    }
}
list makeListEmpty(list l){
    if(l != NULL){
        deleteList(l);
    }
    l =(list)malloc(sizeof(list));
    if(l==NULL){
        printf("\nOut of memory!");
    }
    l->next=NULL;
    return l;
}
void deleteList(list l){
    list P,temp;
    P=l->next;
    l->next=NULL;
    while(P !=  NULL){
        temp=P->next;
        free(P);
        P=temp;
    }
}
void insertInList(edge e,list l){
    num++;
    list temp;
    temp=(list)malloc(sizeof(list));
    temp->num=num;
    temp->e=e;
    l->next=temp;
}
void readFile(){
    FILE * f=fopen("Cities.txt","r");
    if(f==NULL){
        printf("\nError: File not found!");
    }else{
        char line[500];
        char* p;
        char source[50];//course name
        char destination[50];
        int distance;
        int count=0;
        while (!feof(f)){

            fgets(line,sizeof(line),f);
            //printf("\n%s",line);
            if (strcmp(line,"\n")==0)// skips any blank lines that might be in the file
                continue;

            p=strtok(line,"\n");//removes the new line character from the end of the line
            p=strtok(line,"\t" "\t"  );//divides the line where the tab character is located
            int count=0;
            while (p!=NULL){
                tolower(p);
                //printf("\n====%s====",p);
                count++;
                if (count==1){
                    strcpy(source,p);
                   // printf(" source: %s\n",source);
                }else if (count==2){
                    strcpy(destination,p);
                   // printf(" destination: %s\n",destination);
                }else if (count==3){
                    distance=atoi(p);
                   // printf(" distance=%d\n",distance);
                }
                p=strtok(NULL,"\t""\t");
            }
            //inserting here.........
            }
            count=0;   //start of a new line , so counter in 0
        }
        fclose(f);
    }

choice2(){
}
choice3(){
}
int main()
{
    int choice, temp, status;
    int flag=0;
    while(1){
        printf("\n====================Menu==================== ");
        printf("\n(1)Load Cities");
        printf("\n(2)Enter Source City");
        printf("\n(3)Enter Destination City");
        printf("\n(4)Exit");
        printf("\nEnter your choice: ");
        status = scanf("%d", &choice);
            while(status!=1){//to check if the input is valid or not
                while((temp=getchar()) != EOF && temp != '\n');
                printf("\nInvalid input... please enter choice (numbers only): ");
                status = scanf("%d", &choice);
            }
        switch(choice){
        case 1:
            readFile();
            flag=1;
            break;
        case 2:
            if(flag==1){
                choice2();
                flag=2;
            }else{
                printf("\nError: you need to choose 1 first!");
            }
            break;
        case 3:
            if(flag==2){
                choice3();
            }else{
                printf("\nError: you need to choose 2 first!");
            }
            break;
        case 4:
            printf("\nGoodBye~");
            return 0;
            break;
        }
    }
}




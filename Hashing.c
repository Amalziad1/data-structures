#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strings built in functions
#include <stdbool.h> //boolean type and values

struct hashTable{
    char name[100];
    int hour;
    char code[10];
    char department[100];
    char topics[500];
    int status;
};
typedef struct hashTable* table;
typedef struct hashTable* t;

//========================Variables========================
double load_factor;
int collision1=0;
int collision2=0;
 int courseNum=0;
table table1;//table1 for linear hashing
table table2;//table2 for double hashing
int size=19;//Note: chosen 19 because my compiler didn't accept number over 22
            //Note2: 19 because its the largest PRIME number I can choose
//*******************

//********************
 int hash_function(char* input){//general function h()
    int sum=0;
    for (int i=0 ; input[i]!='\0'; i++){
        sum +=  ( (int)input[i]*(i+1));  }

    return sum%size;
}
int hash_function2(char* input){//h2()
    int r=find_primeFor2(size);
    int result=r - (((int)input)%r);
    return result;
}
int linear(int i, char* input){//linear hashing
    return (hash_function(input) + i)% size;
}
int doubleHash(int i, char* input){//double hashing
    return (hash_function(input) + i*hash_function2(input))% 19;
}

table createTable(table temp){

    temp= (table)malloc(size * sizeof(table));
    for (int i=0; i<size; i++){
            strcpy(temp[i].name,""); // initially, all of the cells are empty.
            strcpy(temp[i].code,"");
            strcpy(temp[i].department,"");
            strcpy(temp[i].topics,"");
            temp[i].hour=0;
            temp[i].status = 0;
            //printf("\nlocation %d name %s",i,temp[i].name);
        }
        //printf("\ndone!!!!!");
        return temp;
}
float get_load_factor(int num){//to get load factor value
    load_factor = (float)num/size;
    return load_factor;
}

int check_load_factor(int num,int size){
    load_factor = (float)num/size;
    if (load_factor>=0.65){return 1;}
    else{return 0;}
        }
int find_prime(int n){//first prime that is bigger of the size
       int i;
       int prime=1;
       int v;
       for (i=2; i< (n/2) ;i++){
            if (n%i==0){
                prime=0;
                v=find_prime(n+1);
                break;
            }
        }
      if (prime!=0)
        return n;
}
int find_primeFor2(int n){//to get prime R where R is smaller than TableSize (for h2())
    int prime=1;
    int v;
    for (int i=2; i< (n/2) ;i++){
        if (n%i==0){
            prime=0;
            v=find_primeFor2(n-1);
            break;}        }
    if (prime!=0)
        return n;
}

void insert1(table tab, char name[50],int hour,char code[10],char department[100],char topics[500]){
    int i=0;
    int location= hash_function(name);//find the original location, using the hash function:
    if (strcmp(tab[location].name,"")!=0){//in case there is collision (cell already occupied)
            collision1++;    i++;

                location=linear(i,name);
                while (strcmp(tab[location].name,"")!=0){
                        collision1++;    i++;
                        location=linear(i,name);   }
                courseNum++;//incrementing course number (which is the occupied number)

                strcpy(tab[location].name,name);
                tab[location].hour=hour;
                strcpy(tab[location].code,code);
                strcpy(tab[location].department,department);
                strcpy(tab[location].topics,topics);
                tab[location].status=1;
                //emptying parameters to avoid interactions in the table
                name="";
                hour=0;
                code="";
                department="";
                topics="";

    }else{ //else if the cell is not already occupied (no collision)
                strcpy(tab[location].name,name);
                //printf("\nName at %d is %s",location,tab[location].name);
                tab[location].hour=hour;
                strcpy(tab[location].code,code);
                strcpy(tab[location].department,department);
                strcpy(tab[location].topics,topics);
                tab[location].status=1;
                courseNum++;//incrementing course number (which is the occupied number)

                //emptying parameters to avoid interactions in the table
                name="";
                hour=0;
                code="";
                department="";
                topics="";

                }

}//end of insert function
void insert2(table tab, char name[50],int hour,char code[10],char department[100],char topics[500]){
    int i=0;
    int location= hash_function(name);//find the original location, using the hash function:
    if (strcmp(tab[location].name,"")!=0){//in case there is collision (cell already occupied)
            collision2++;    i++;

                location=doubleHash(i,name);
                while (strcmp(tab[location].name,"")!=0){
                        collision2++;    i++;
                        location=doubleHash(i,name);   }

                strcpy(tab[location].name,name);
                tab[location].hour=hour;
                strcpy(tab[location].code,code);
                strcpy(tab[location].department,department);
                strcpy(tab[location].topics,topics);
                tab[location].status=1;
                //emptying parameters to avoid interactions in the table
                name="";
                hour=0;
                code="";
                department="";
                topics="";

    }else{ //else if the cell is not already occupied (no collision)
                strcpy(tab[location].name,name);
                tab[location].hour=hour;
                strcpy(tab[location].code,code);
                strcpy(tab[location].department,department);
                strcpy(tab[location].topics,topics);
                tab[location].status=1;

                //emptying parameters to avoid interactions in the table
                name="";
                hour=0;
                code="";
                department="";
                topics="";
                }
}//end of insert function
 void rehash_function1(table oldt, table newt){
        for(int i=0; i<size; i++){
                if(strcmp(oldt[i].name,"")!=0){
                    insert1(newt,oldt[i].name,oldt[i].hour,oldt[i].code,oldt[i].department,oldt[i].topics);
                    //insert2(newt,oldt[i].name,oldt[i].hour,oldt[i].code,oldt[i].department,oldt[i].topics);
                }
            }
            oldt=createTable(oldt);//emptying the old table
            oldt=newt;//making the old table equals the new one
        }
void rehash_function2(table oldt, table newt){
        for(int i=0; i<size; i++){
                if(strcmp(oldt[i].name,"")!=0){
                   // insert1(newt,oldt[i].name,oldt[i].hour,oldt[i].code,oldt[i].department,oldt[i].topics);
                    insert2(newt,oldt[i].name,oldt[i].hour,oldt[i].code,oldt[i].department,oldt[i].topics);
                }
            }
        }
void readFile(){
    FILE * f=fopen("offered_courses.txt","r");
    if(f==NULL){
        printf("\nError: File not found!");
    }else{
        char line[500];
        char* p;
        char name[100];//course name
        char department[30];
        int hour=0;
        char code[10];
        char topics[300];
        while (!feof(f)){

            fgets(line,sizeof(line),f);
            //printf("\n%s",line);
            if (strcmp(line,"\n")==0)// skips any blank lines that might be in the file
                continue;

            p=strtok(line,"\n");//removes the new line character from the end of the line
            p=strtok(line,":" "#" "#" "/" );//divides the line where the tab character is located
            int count=0;
            while (p!=NULL){
                tolower(p);
                //printf("\n====%s====",p);
                count++;
                //printf("\n (%d)-------------name: %s\n",count, p);
                if (count==1){
                    strcpy(name,p);
                    //printf(" name: %s\n",name);
                }else if (count==2){
                    hour=atoi(p);//parsing value of p in integer variable
                    //printf(" hour %d\n",hour);
                }else if (count==3){
                    strcpy(code,p);
                    //printf(" code %s\n",code);
                }else if (count==4){
                    strcpy(department,p);
                    //printf(" department %s\n",department);
                }else if (count==5){
                    strcpy(topics,p);
                    //printf(" topics %s\n",topics);
                }
                p=strtok(NULL,":" "#" "#" "/");
            }
            insert1(table1,name,hour,code,department,topics);
            insert2(table2,name,hour,code,department,topics);
            int s=check_load_factor(courseNum,size);
            if(s==1){//rehashing if table size reached the max load of the table
                table oldt1=table1;
                table oldt2=table2;
                int newsize=find_prime(size);
                size = newsize;//assigning new size to the oldest
                table newt1;
                newt1=createTable(newt1);
                table newt2;
                newt2=createTable(newt2);
                rehash_function1(oldt1,newt1);
                rehash_function2(oldt2,newt2);
            }
            count=0;   //start of a new line , so counter in 0
        }
        fclose(f);
    }
}
void print_table(table tab){
    int size=19;
    for (int j=0; j<size; j++){
        printf("\n ^^^^^^^^^^location #(%d)^^^^^^^^^^ ",j);
        printf("\nCourse name: %s",tab[j].name);
        printf("\nCredit hours: %d",tab[j].hour);
        printf("\nCode: %s ",tab[j].code);
        printf("\nDepartment: %s",tab[j].department);
        printf("\nTopics: %s",tab[j].topics);
        }
    printf("\nNumber of courses: %d\n",courseNum); }


int search_element(table tab,  char name[100]){
    tolower(name);
            int i=0; int location;
            for (i=0; i<size; i++){
                if(strcmp(tab[i].name,name)==0)
                    {location=i;
                    break;}

                else{
                    location=-1;
                    continue;}   }

            return location;    }
void get_element(table tab,  char name[100]){
            tolower(name);
            int location;
            for (int i=0; i<size; i++){
                if(strcmp(tab[i].name,name)==0){
                    location=i;
                    printf("\nCourse at location %d is: %s",i,tab[i].name);
                    printf("\nCourse code: %s",tab[i].code);
                    printf("\nCourse department: %s",tab[i].department);
                    printf("\nCourse credit hours: %d",tab[i].hour);
                    printf("\nCourse topics are: %s",tab[i].topics);
                    break;}

                else{
                    location=-1;
                    continue;}   }

            return location;    }
void delete_element(table tab,  char* name){

            int s= search_element(tab,name);
            if (s!=-1){//if s is -1 then not found
                printf("\n-->course to delete: %s ",tab[s].name);
                strcpy(tab[s].name,"---");
                strcpy(tab[s].code,"---");
                strcpy(tab[s].department,"---");
                strcpy(tab[s].topics,"---");
                tab[s].hour=0;
                tab[s].status=0;
                courseNum--;
                }
            else
                printf("course (%s) is not found, could not delete ",name); }
void printMenu(){
    printf("\n======================Menu========================");
    printf("\n1.Print hashed tables");
    printf("\n2.Print table size and load factor");
    printf("\n3.Print the used hash functions");
    printf("\n4.Insert a new course");
    printf("\n5.Search for a course");
    printf("\n6.Delete a course ");
    printf("\n7.Compare between the two methods in terms of number of collisions occurred");
    printf("\n8.Save changes and exit");
    printf("\n9.Exit without saving");
    printf("\n\nEnter your choice: ");
}
void choice4(){
    char name[50];
    int credit=0, temp_h, status_h;//temp used to collect garbage characters
    int num,temp_n,status_n;
    char Ccode[10];
    char dep[100];
    char topics[500];
    printf("\nEnter course name: ");
    scanf("%s",name);
    tolower(name);
    int temp1=search_element(table1,name);
    int temp2=search_element(table2,name);
    if(temp1!=-1 ){
        printf("\nError: the name is already exists");
    }else{
        printf("Enter course's credit hours: ");
        status_h = scanf("%d", &credit);
        while(status_h!=1){//to check if the input is valid or not
            while((temp_h=getchar()) != EOF && temp_h != '\n');
            printf("\nInvalid input... please enter choice (numbers only): ");
            status_h = scanf("%d", &credit);
        }
        printf("\nEnter code: ");
        scanf("%s",Ccode);
        tolower(Ccode);
        printf("\nEnter department: ");
        scanf("%s",dep);
        tolower(dep);
        printf("\nEnter number of topics: ");
        status_n = scanf("%d", &num);
        while(status_n!=1){//to check if the input is valid or not
            while((temp_n=getchar()) != EOF && temp_n != '\n');
            printf("\nInvalid input... please enter number of topics (numbers only): ");
            status_n = scanf("%d", &num);
        }
        for(int i=0;i<num;i++){
            printf("\nEnter topic #%d",i+1);
            char topic[50];
            scanf("%s",topic);
            tolower(topic);
            strcat(topic,",");
            strcat(topics,topic);
        }
        insert1(table1,name,credit,Ccode,dep,topics);
        insert2(table2,name,credit,Ccode,dep,topics);
        int s=check_load_factor(courseNum,size);
            if(s==1){//rehashing if table size reached the max load of the table
                table oldt1=table1;
                table oldt2=table2;
                int newsize=find_prime(size);
                size = newsize;
                table newt1;
                newt1=createTable(newt1);
                table newt2;
                newt2=createTable(newt2);
                rehash_function1(oldt1,newt1);
                rehash_function2(oldt2,newt2);
            }
        printf("Insertion is done successfully!");
    }
}
void choice5(){
    char name[100];
    char choice[10];
    printf("\nEnter 'L' to search in linear hashing table");
    printf("\nEnter 'D' to search in double hashing table");
    scanf("%s",choice);
    toupper(choice);
    bool stat=true;
    while(stat==true){
        if(strcmp(choice,"L")){
        printf("\nEnter course name: ");
        scanf("%s",name);
        tolower(name);
        int i=search_element(table1,name);
        if(i==-1){
            printf("\nCourse %s does not exist",name);
        }else{
            printf("\nCourse location in linear hashing table is: %d",i);
            get_element(table1,name);
        }
        stat=false;
    }else if(strcmp(choice,"D")){
        printf("\nEnter course name: ");
        scanf("%s",name);
        tolower(name);
        int i=search_element(table2,name);
        if(i==-1){
            printf("\nCourse %s does not exist",name);
        }else{
            printf("\nCourse location in double hashing table is: %d",i);
            get_element(table2,name);
        }
        stat=false;
    }else{
        printf("\nError: bad input, please enter L or D: ");
        scanf("%s",choice);
        toupper(choice);
    }
    }
}
void choice6(){
    char name[100];
    printf("Enter course name to delete: ");
    scanf("%s",name);
    tolower(name);
    delete_element(table1,name);
    //courseNum--;
}
void choice7(){
    printf("\nComparing between linear hashing and double hashing:");
    printf("\n\tLinear hashing collision numbers: %d",collision1);
    printf("\n\tDouble hashing collision numbers: %d",collision2);
}
void choice8(){
    FILE *file=fopen("saved_courses.txt","w");
    if(file==NULL){
        printf("\nError: file not found");
    }else{
    for (int j=0; j<4; j++){//here again the compiler exited the program because the size is large over it
                                //it accepted at most 9! -don't know why....-

        if(strcmp(table2[j].name,"")!=0){
            fprintf(file,"%s : %d # %s # %s / %s \n",j,table2[j].name,table2[j].hour,table2[j].code,table2[j].department,table2[j].topics);
        }
    }}
    printf("\n");
    fclose(file);
    printf("\nSaving changes is done successfully!");
}
int main()
{
    printf("\n============================Welcome to My Project=========================");
    printf("\n==============================Courses Manager=============================");
    printf("\n===========================By Amal Ziad 1192141===========================");
    printf("\n=================================Starting=================================");
    table1=createTable(table1);
    printf("\n*********Table 1 created*********");
    table2=createTable(table2);
    printf("\n*********Table 2 created*********");
    readFile();//reading file and storing data in the two tables
    printf("\n*********File is read************");
    while(true){
        printMenu();
        int choice, temp, status;//temp used to collect garbage characters
        status = scanf("%d", &choice);
        while(status!=1){//to check if the input is valid or not
            while((temp=getchar()) != EOF && temp != '\n');
            printf("\nInvalid input... please enter choice (numbers only): ");
            status = scanf("%d", &choice);
        }
        switch(choice){
        case 1:
            printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ For table 1 (linear hashing)+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ ");
            print_table(table1);
            printf("\n\n");
            printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ For table 2 (double hashing)+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ ");
            print_table(table2);
            printf("\n\n");

            break;
        case 2:
            printf("\nTable size (for both tables): 19");
            printf("\nTable occupied locations number (for both tables): %d",courseNum);
            float number;
            number=get_load_factor(courseNum);
            printf("\nLoad factor (for both tables): %f",number);

            break;
        case 3:
            printf("\nThe used hash functions are: ");
            printf("\n(1)Linear hashing: h(name)=(h1(name)+i)%size");
            printf("\n(2)Double hashing: h(name)=(h1(name)+(i*h2(name))%size)");
            break;
        case 4:
            choice4();
            break;
        case 5:
            choice5();
            break;
        case 6:
            choice6();
            break;
        case 7:
            choice7();
            break;
        case 8:
            choice8();
            printf("\nExisting...");
            printf("\nGood bye~");
            return false;
            break;
        case 9:
            printf("\nExisting...");
            printf("\nGood bye~");
            return false;
            break;
        default:
            printf("\Error: wrong option, enter choice from 1 to 9: ");
            break;
        }

    }
    return 1;
}


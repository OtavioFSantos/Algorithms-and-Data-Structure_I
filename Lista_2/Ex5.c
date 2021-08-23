#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[30];
    int age;
    int height;
}Person;

int main(){
    int choice = 0, size = 0;
    Person *p;
    p=(Person *)calloc(1, sizeof(Person));

    do{
        printf("\nAdd person:\n");
        printf("Name: "); scanf("%s",(p+size)->name);
        printf("Age: "); scanf("%d",&(p+size)->age);
        printf("Height: "); scanf("%d",&(p+size)->height);
        size++;

        printf("\nDo you wish to add someone else(1.yes 2.no)? "); scanf("%d", &choice);
        if(choice == 1){
            p=(Person *)realloc(p, sizeof(Person)*(size+1));
        }
    }while(choice == 1);

    for(int i = 0; i < size; i++){
        printf("\nPerson[%d]: Name: %s, Age: %d, Height: %d", i, (p+i)->name, (p+i)->age, (p+i)->height);
    }
    
    printf("\n\nBye!\n\n");
    free(p);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10


int count = 0;
char names[10][20];
int size[10];


/*
This function returns nothing
When this function is called
it will exit the program
*/
int Quit(void)
{
        exit(0);
}

/*
This function returns nothing
When called, this will aks the user
for their name and size of party
after scanning, it will add both sseperately to
arrays: names and size, respectively
It will increment the count to add to the
next position in the array
*/
void insert()
{
        char s[10];
        int a;
        printf("Please enter your name, no more than 20 characters\n");
        scanf("%s", s);
        strcpy(names[count], s);
        printf("Please enter the size of your group\n");
        scanf("%d", &a);
        size[count] = a;
        count++;
}


/*
This function returns nothing
When called, it asks the user for the size of the current opening
after scanning, it uses a for loop until it finds the
size value that corresponds to the users input
Once found, this functin prints the name and size of the group that is ready
Then, every element in each list is replaced with the one below it
count is decreased by one so that the user can insert to the correct position again
*/
void removeGroup()
{
        int flag = 0;
        if(count == 0)
        {
                printf("Sorry, the list is already empty\n");
        }
        else
        {
                int a = 0;
                printf("What is the size of the current opening?\n");
                scanf("%d", &a);
                int i = 0;
                for(i = 0; i < SIZE; i++)
                {
                        if(size[i] == a)
                        {
                                printf("%s, Your table for %d is ready\n", names[i], size[i]);
                                flag = 1;
                                for(int j = i; j < SIZE; j++)
                                {
                                        strcpy(names[j], names[j+1]);
                                        size[j] = size[j+1];
                                }
                        count--;
                        int i = SIZE;
                        }
                }
                if(flag == 0)
                {
                        printf("There is no reservation of that size\n");
                }
        }

}

/*
This funtion returns nothing
uses a for loop to print out
both the names array
and the size array side by side
*/
void list()
{       
        for(int i = 0; i < SIZE; i++)
        {       
                printf("Group name: %s, Size: %d\n", names[i], size[i]);
        }
}


/*
This is the main function
First, the all the positions in
the names array are set to NULL
Then, in an infinite loop the main menu of options
is printed and waits for the users selection
Depending on the users selection
a certain function will be called, either
insert, removeGroup, list, or Quit
*/
int main(void)
{
        for(int i = 0; i < SIZE; i++)
        {
                names[i][0] = '\0';
        }

        for(;;)
        {
                printf("Please Choose an Option:\n 1-Add Guest\n 2-Remove Guest\n 3-Show Guest List\n 0-Exit\n");
                int a;
                scanf("%d", &a);

        if(a == 1)
        {
                if(count == 10)
                {
                        printf("Sorry, the list is full\n");
                }
                else
                {
                        insert();
                }
        }

        if(a == 2)
        {
                removeGroup();

        }
        if(a == 3)
        {
                list();
        }

        if(a == 0)
        {
                Quit();
        }

        }

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10




/*
Initialize global variables, arrays, structure, and array of structures
*/
typedef struct list
{
char names[20];
int size;
} LIST;

int count = 0;
LIST list[10];



/*
Arguments: None
Return Type: int, 0 exits program
Functionality: Quits the program
*/
int Quit(void)
{       
        exit(0);
}

/*
Arguments: String s
Return Type: int, 1 if the same, 0 if not 
functionality: checks if a string is a duplicate in the array
*/

int check_duplicate(char s[])
{
	LIST *p;
	p = list;
	for(int i = 0; i < count; p++, i++)
	{
		if((strcmp(s, p->names)) == (0))
		{
			return 1;
		}
	}	
	return 0;
}

/*
Arguments: None
Return Type: Void
Functionality: Finds and prints all sizes in the list that are less than or equal to the user input 
*/

void search_size()
{
	LIST *p;
	p = list;
	int flag = 0;
	int a;
	printf("Please enter a size\n");
	scanf("%d", &a);

	
	printf("Here are all the parties with a size smaller than or equal to %d:\n", a);
	for(int i = 0; i < count; p++, i++)
	{
		
		if(p->size <= a && p->size != 0)
		{
			printf("%s, %d\n", p->names, p->size);
			flag = 1;
		}
	}
	if(flag == 0)
	{
		printf("There is no one of that size\n");
	}
}

/*
Arguments: None
Return Type: void
Functionality: Inserts a string and a size into the structure form users input, calls check duplicate to not allow duplicate names  
*/
void insert()
{       

        char s[10];
        int a;
        printf("Please enter your name, no more than 20 characters\n");
        scanf("%s", s); 
        printf("Please enter the size of your group\n");
        scanf("%d", &a);

	if(check_duplicate(s) == 1)
	{
		printf("Sorry, there is already a party with that name\n");
		return;
	}
	strcpy(list[count].names, s);
        list[count].size = a;
        count++;
}


/*
Arguments: None
Return Type: Void
Functionality: Removes a name and size from the list and moves all the other names and sizes in the arrary of structures up one position, has flags if there  is no reservation of the users input
*/
void delete()
{
	LIST *p;
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
		p = list;
        	for(int i = 0; i < count; p++,  i++)
		{
			if(p->size == a)
			{
				printf("%s, Your table for %d is ready\n", p->names, p->size);
				flag = 1;
				for(int j = i; j < count; p++, j++)
                        	{       
                                	strcpy(p->names, (p+1)->names);
                                	p->size = (p+1)->size;
                        	}
			count--;
			int i = count; 
			}
		}
		if(flag == 0)
		{
			printf("There is no reservation of that size\n");
		}
	}
}
      

/*
Arguments: None
Return Type: Void
Functionlity: Uses a for loop to print out all names and sizes in the array of structures
*/
void show()
{
	LIST *p;
	p = list;
        for(int i = 0; i < count; p++, i++)
        {
			printf("Group name: %s, Size: %d\n", p->names, p->size);
        }
}


/*
Arguments: None
return Type: void
Functionality: In an infinite loop the main menu of options
is printed and waits for the users selection
Depending on the users selection
a certain function will be called, either
insert, delete, show, search_size, or Quit
*/
int main(void)
{

        for(;;)
        {
                printf("Please Choose an Option:\n 1-Add Guest\n 2-Remove Guest\n 3-Show Guest List\n 4-Search Size\n 0-Exit\n");
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
                delete();
        }

        if(a == 3)
        {
                show();
        }

	if(a == 4)
	{
		search_size();
	}

        if(a == 0)
        {
                Quit();
        }

        }

return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10


/*
Initialize global variables, arrays, structure, union, and array of structures
*/

union info
{
        char name[20];
        int years;
	float avg;
};

typedef struct list
{
	char names[20];
	int size;
	int occasion;
	union info extra;
}LIST;

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
it also checks for occasions 1, 2, or 3 in and prints out the repstive birthday, anniversary, or age from the union

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
		printf("-------------------------------------------------------------------------------------\n");		
                if(p->size <= a && p->size != 0)
                {
                        printf("%s, %d\n", p->names, p->size);
			if(p->occasion == 1)
                        {
                                printf("Occasion: Birthday       Birthday Name: %s\n", p->extra.name);
                        }
                        if(p->occasion == 2)
                        {
                                printf("Occasion: Anniversary    Years: %d\n", p->extra.years);
                        }
                        if(p->occasion == 3)
                        {
                                printf("Occasion: Other          Avergae Age of Group: %.2f\n", p->extra.avg);
                        }
                        flag = 1;
                }
        }
	printf("-------------------------------------------------------------------------------------\n");
        if(flag == 0)
        {
                printf("There is no one of that size\n");
        }
}

/*
Arguments: None
Return Type: void
Functionality: Inserts a string and a size into the structure form users input, calls check duplicate to not allow duplicate names
It also asks the user if they have a special occasion, based on the users input, it adds either a birthday name, anniversary number, or an age float from the union
*/
void insert()
{

        char s[10];
        int a;
	int b;
        printf("Please enter your name, no more than 20 characters\n");
        scanf("%s", s);
        printf("Please enter the size of your group\n");
        scanf("%d", &a);

        if(check_duplicate(s) == 1)
        {
                printf("Sorry, there is already a party with that name\n");
                return;
	}
	
	printf("What is the occasion?\n\t Birthday - 1, Anniversary - 2, Other - 3\n");
	scanf("%d", &b);

	if(b == 1)
	{
		list[count].occasion = 1;
	}

	if(b == 2)
	{
		list[count].occasion = 2;
	}

	if(b == 3)
	{
		list[count].occasion = 3;
	}

	strcpy(list[count].names, s);
        list[count].size = a;

	if(b == 1)
	{
		printf("Whose Birthday is it?\n");
		scanf("%s", list[count].extra.name);
	}
	if(b == 2)
	{
		printf("How many years are you celebrating?\n");
		scanf("%d", &list[count].extra.years);
	}
	if(b == 3)
	{
		printf("Please enter the average age of the group\n");
		scanf("%f", &list[count].extra.avg);
	}
		
        count++;
}


/*
Arguments: None
Return Type: Void
Functionality: Removes a name and size from the list and moves all the other names and sizes in the arrary of structures up one position, has flags if there  is no reservation of the users input
It also, checks the occasion and removes the birthday, or anniversary, or average age in the union
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
					p->occasion = (p+1)->occasion;
					
					if((p+1)->occasion == 1)
					{
						strcpy(p->extra.name, (p+1)->extra.name);
					}
					if((p+1)->occasion == 2)
					{
						p->extra.years = (p+1)->extra.years;
					}
					if((p+1)->occasion == 3)
					{
						p->extra.avg = (p+1)->extra.avg;
					}
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
Functionlity: Uses a for loop to print out all names and sizes in the array of structures, also checks occasions and prints the birthday name, anniversary year, or age value from the union
*/
void show()
{
        LIST *p;
        p = list;
        for(int i = 0; i < count; p++, i++)
        {
			printf("-------------------------------------------------------------------------------------\n");
                        printf("Group name: %s, Size: %d\n", p->names, p->size);
			if(p->occasion == 1)
			{
				printf("Occasion: Birthday       Birthday Name: %s\n", p->extra.name);
			}
			if(p->occasion == 2)
			{
				printf("Occasion: Anniversary    Years: %d\n", p->extra.years);
			}
			if(p->occasion == 3)
			{
				printf("Occasion: Other          Avergae Age of Group: %.2f\n", p->extra.avg);
			}
        }
	printf("-------------------------------------------------------------------------------------\n");
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define NODE struct node

/*
Initialize global NODE pointers, and node struct, declare all functions
*/
struct node
{
char names[20];
int size;
NODE *next;
};

NODE *head = NULL;                                                             
NODE *tail;

void insert();
int check_duplicate(char s[]);
void delete();
void show();
void search_size();
int Quit(void);
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
                        insert();       
                 }

                 else if(a == 2)
                 {
                        delete();
                 }

                 else if(a == 3)
                 {
                        show();
                 }

                 else if(a == 4)
                 {
                        search_size();
                 }

                 else if(a == 0)
                 {
                        Quit();
                 }
                 else
                 {
                        printf("That is not a valid option\n");
                 }

        }

return 0;
}


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
functionality: checks if a string is a duplicate in the linked list
*/

int check_duplicate(char s[])
{
        NODE *p = head;
	while(p != NULL)
	{
		if(strcmp(s, p->names) == 0)
		{
			return 1;
		}
		else
		{
			p = p->next;
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
        NODE *p;
        p = head;
        int a;
        printf("Please enter a size\n");
        scanf("%d", &a);


        printf("Here are all the parties with a size smaller than or equal to %d:\n", a);
        while(p != NULL)
	{
		if(p->size <= a)
                {       
                        printf("%s, %d\n", p->names, p->size);
			p = p->next;
                }	
	}
}


/*
Arguments: None
Return Type: void
Functionality: Inserts a string and a size into the linked list form users input, calls check duplicate to not allow duplicate names
*/
void insert()
{
	int a;
	char s[20];
        NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));

        printf("Please enter your name, no more than 20 characters\n");
        scanf("%s", s);
	if(check_duplicate(s) == 1)
        {       
                printf("Sorry, there is already a party with that name\n");
                return;
        }
        printf("Please enter the size of your group\n");
        scanf("%d", &a);
	
	strcpy(temp->names, s);
	temp->size = a;
	if(head == NULL)
	{
		temp->next = NULL;
		head = temp;
		tail = temp;
	}
	else
	{
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	
        
}


/*
Arguments: None
Return Type: Void
Functionality: Removes a name and size from the list
*/
void delete()
{
        NODE *p = head;
	NODE *q = head;
        int flag = 0;
        if(head == NULL)
        {
                printf("Sorry, the list is already empty\n\n");
        }
        else
        {
                int a = 0;
                printf("What is the size of the current opening?\n");
                scanf("%d", &a);
         	p = head;                       
                while(q != NULL)
		{
			if(q->size == a)
			{
			printf("%s, Your table for %d is ready\n", q->names, q->size);
			flag = 1;
				if(head == tail)
				{
					head = NULL;
					tail = NULL;
				}
				else if(q == head)
				{
					head = head->next;
					free(q);
				}
				else if(q == tail)
				{
					tail = p;
					tail->next = NULL;
					free(q);
				}
				else
				{
					p->next = q->next;
					free(q);
				}
			return;	
			}
		p = q;
		q = q->next;
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
Functionlity: prints out all names and sizes in the list
*/
void show()
{
        NODE *p = head;
	if(head == NULL)
	{
		printf("Sorry the list is empty");
		return;
	}
	while(p != NULL)
	{
		printf("Group name: %s, Size %d\n", p->names, p->size);
		p = p->next; 
	}
}




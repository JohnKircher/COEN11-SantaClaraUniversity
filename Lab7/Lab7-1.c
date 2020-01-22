#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define NODE struct node
#define LIST struct list

/*
Initialize global NODE pointers, and node struct, declare all functions
*/
struct node
{
char names[20];
int size;
NODE *next;
};

struct list
{
NODE *head;
NODE *tail;
};

LIST stuff[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};


void readFile(char *file);
void writeFile(char *file);
void insert(char *name, int number);
int check_duplicate(char s[]);
void delete();
void show();
void search_size();
int Quit(void);

/*
Arguments: int argc, char *argv[]
return Type: void
Functionality: In an infinite loop the main menu of options
is printed and waits for the users selection
Depending on the users selection
a certain function will be called, either
insert, delete, show, search_size, or Quit
*/
int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("The file name is missing\n");
		return 0;
	}
	else if(argc > 2)
	{
		printf("Too many inputs\n");
		return 0;
	}
	readFile(argv[1]);

        for(;;)
        {
                 printf("Please Choose an Option:\n 1-Add Guest\n 2-Remove Guest\n 3-Show Guest List\n 4-Search Size\n 0-Exit\n");
                 int a;
                 scanf("%d", &a);

                 if(a == 1)
                 {
                 	int b;   
        		char s[20];     
        
        		printf("Please enter your name, no more than 20 characters\n");
        		scanf("%s", s);
        		if(check_duplicate(s) == 1)
        		{
                		printf("Sorry, there is already a party with that name\n");
                		return 0;
        		}
        		printf("Please enter the size of your group\n");
        		scanf("%d", &b);
			insert(s, b);       
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
			writeFile(argv[1]);
			NODE *p;
			for(int i = 0; i < 4; i++)
			{
				while(stuff[i].head != NULL)
				{
					p = stuff[i].head;
					stuff[i].head = stuff[i].head->next;
					free(p);
				}
			}
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
Arguments: char *file
Return Type: void
Functionality: recieves information from file
*/
void readFile(char *file)
{
	FILE *fp;
	NODE *p;
	char s[] = " ";
	int d = 0;
	if((fp = fopen(file, "r")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	fseek(fp, 41, SEEK_SET);
	while(fscanf(fp, "%s\t\t%d\n", s, &d) == 2)
	{
		insert(s, d);
	}
	fclose(fp);
	return;
}

/*
Arguments: char *file
Return Type: void
Functionality: writes information to the file
*/
void writeFile(char *file)
{
	FILE *fp;
	char FL[] = "Name\t\tGroup Size\n";
	char SL[] = "-----------------------\n";
	if((fp = fopen(file, "w")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	fprintf(fp, "%s\n%s\n", FL, SL);
	NODE *p;
	for(int i = 0; i < 4; i++)
	{
		p = stuff[i].head;
		while(p != NULL)
		{
			fprintf(fp, "%s\t\t%d\n", p->names, p->size);
			p=p->next;		
		}
	}
	fclose(fp);
	return;
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
        NODE *p;
	for(int i = 0; i < 4; i++)
	{
		p = stuff[i].head;
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
	int a;
	printf("Please enter a size");
	scanf("%d", &a);
	NODE *p;
        p = stuff[0].head;
        for(int i = 0; i < 4; i++)
        {
                p = stuff[i].head;
                while(p != NULL)
                {
			if(p->size <= a)
			{
                        	printf("Name: %s, Size: %d\n", p->names, p->size);
			}
		p = p->next;
                }
        }
}


/*
Arguments: char *name, int number
Return Type: void
Functionality: Inserts a string and a size into the correct linked list from users input, calls check duplicate to not allow duplicate names
*/
void insert(char *name, int number)
{
        NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));
	if((number == 1) || (number == 2))
	{
		if(stuff[0].head == NULL)
		{
			temp->next = NULL;
			stuff[0].head = stuff[0].tail = temp;
		}
		else
		{
			temp->next = NULL;
			stuff[0].tail->next = temp;
			stuff[0].tail = temp;
		}
	strcpy(temp->names, name);
        temp->size = number;
	}

	else if((number == 3) || (number == 4))
        {       
                if(stuff[1].head == NULL)
                {       
                        temp->next = NULL;
                        stuff[1].head = stuff[1].tail = temp;
                }
                else
                {       
                        temp->next = NULL;
                        stuff[1].tail->next = temp;
                        stuff[1].tail = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }

	else if((number == 5) || (number == 6))
        {
                if(stuff[2].head == NULL)
                {
                        temp->next = NULL;
                        stuff[2].head = stuff[2].tail = temp;
                }
                else
                {
                        temp->next = NULL;
                        stuff[2].tail->next = temp;
                        stuff[2].tail = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }

	else if(number > 6)
        {
                if(stuff[3].head == NULL)
                {
                        temp->next = NULL;
                        stuff[3].head = stuff[3].tail = temp;
                }
                else
                {
                        temp->next = NULL;
                        stuff[3].tail->next = temp;
                        stuff[3].tail = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }	
}


/*
Arguments: None
Return Type: Void
Functionality: Removes a name and size from the correct list
*/
void delete()
{
        NODE *p;
	NODE *q;
        int flag = 0;
	
        
                int a = 0;
                printf("What is the size of the current opening?\n");
                scanf("%d", &a);                       
		for(int i = 0; i <= a/2.1; i++)
		{
			p = q = stuff[i].head;
                        while(q != NULL)
                        {       
                                if(a >= q->size)
                                {       
                                        printf("%s, Your table for %d is ready\n", q->names, q->size);
                                        flag = 1;
                                        if(stuff[i].head == stuff[i].tail)
                                        {       
                                                stuff[i].head = NULL;
                                                stuff[i].tail = NULL;
                                        }
                                        else if(q == stuff[i].head)
                                        {       
                                                stuff[i].head = stuff[i].head->next;
                                                free(q);
                                        }
                                        else if(q == stuff[i].tail)
                                        {       
                                                stuff[i].tail = p;
                                                stuff[i].tail->next = NULL;
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
		}	                                                                                                                                    
        	if(flag == 0)
        	{
       			printf("There is no reservation of that size\n");
        	}
}



/*
Arguments: None
Return Type: Void
Functionlity: prints out all names and sizes in from all lists
*/
void show()
{
	NODE *p;
	p = stuff[0].head;
	for(int i = 0; i < 4; i++)
	{
		p = stuff[i].head;
		while(p != NULL)
		{
			printf("Name: %s, Size: %d\n", p->names, p->size);
			p = p->next;
		}
	}
}



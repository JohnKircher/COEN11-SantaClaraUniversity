#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
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

void *auto_save(void *argc);
void readBinary(char *argc);
void reverse_recursive(NODE *p);
void reverse();
void backwards_recursive(char *p);
void backwards();
void readFile(char *file);
void writeFile(char *file);
void insert(char *name, int number);
int check_duplicate(char s[]);
void delete();
void show();
void search_size();
void quit_recursive(NODE *p);
void quit();

pthread_mutex_t  mutex;
pthread_t thread;

/*
Arguments: int argc, char *argv[]
return Type: void
Functionality: In an infinite loop the main menu of options
is printed and waits for the users selection
Depending on the users selection
a certain function will be called, either
insert, delete, show, search_size, reverse order, 
backwards ames, read to binary, or quit
*/
int main(int argc, char *argv[])
{
	
	if(argc < 3)
	{
		printf("The file name(s) is missing\n");
		return 0;
	}
	readFile(argv[1]);
	
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread, NULL, auto_save, (void *) argv[2]);
	 		
        for(;;)
        {
                 printf("Please Choose an Option:\n 1-Add Guest\n 2-Remove Guest\n 3-Show Guest List\n 4-Search Size\n 5-Reverse Order\n 6-Backwards Names\n 7-Read to Binary\n 0-Exit\n");
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
        		}
			else
			{
        		printf("Please enter the size of your group\n");
        		scanf("%d", &b);
			insert(s, b);
			}       
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
		 else if(a == 5)
		 {
			reverse();	
		 }
		 else if(a == 6)
		 {
			backwards();
		 }
		 else if(a == 7)
		 {
			readBinary(argv[2]);
		 }
                 else if(a == 0)
		 {
			pthread_mutex_lock(&mutex);
			pthread_cancel(thread);
			pthread_mutex_unlock(&mutex);
			writeFile(argv[1]);
			quit();
			return 0;
			
                 }
                 else
                 {
                        printf("That is not a valid option\n");
                 }

        }

return 0;
}

/*
Arguments: char *arg
Return Type: void
Functionality: Reads informaiton to the binary file
*/
void readBinary(char *arg)
{
	FILE *fp;
	char name[20];
	int size;
	NODE p;

	pthread_mutex_lock(&mutex);
	fp = fopen(arg, "rb");
	if(fp == NULL)
	{
		printf("Cannot Open Binary File\n");
		return;
	}
	while(fread(&p, sizeof(NODE), 1, fp) > 0)
	{
		printf("%s, %d\n", p.names, p.size);
	}

	fclose(fp);
	pthread_mutex_unlock(&mutex);
	return;
}
 
/*
Arguments: void *arg
Return Type: void *
Fucntionality: Auto Saves/writes information every 15 seconds to the binary file
*/
void * auto_save(void *arg)
{
	char *filename = (char*)arg;
	FILE *fp;
	NODE *p;

	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("Started Auto-Saving\n");
		fp = fopen(filename, "wb");
		if(fp == NULL)
		{
			printf("Bad File\n");
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		for(int i = 0; i < 4; i++)
		{
			p = stuff[i].head;
			while(p != NULL)
			{
				fwrite(p, sizeof(NODE), 1, fp);
				p = p->next;
			}
		}
		fclose(fp);
		printf("Finished Auto-Saving\n");
		pthread_mutex_unlock(&mutex);
		sleep(15);
	}
	return NULL;
}

/*
Arguments: NODE pointer
Return Type: void
Functionalty: Recursively frees all the cells
*/
void quit_recursive(NODE *p)
{
	if(p == NULL)
	{
		return;
	}
	else
	{
		quit_recursive(p->next);
		free(p);
	}
}

/*
Arguments: None
Return Type: void
Functionality: loops through arrary of linked list and calls recursive function: quit_recursive
*/
void quit()
{
	NODE *p;
	for(int i = 0; i < 4; i++)
	{
		p = stuff[i].head;
		if(p == NULL)
		{
			continue;
		}
		else
		{
			quit_recursive(p);
		}
	}
}


/*
Arguemnts: NODE pointer
Return Type: void
Functionality: Prints all members of each linked list in reverse order
*/
void reverse_recursive(NODE *p)
{
	if(p == NULL)
	{
		return;
	}
	reverse_recursive(p->next);
	printf("Name: %s, Size: %d\n", p->names, p->size);
}

/*
Arguments: None
Return Type: void
Functionality: loops through array of linked lists and calls recursive function: reverse_recursive
*/
void reverse()
{
	NODE *p;
	for(int i = 0; i < 4; i++)
	{
		p = stuff[i].head;
		if(p == NULL)
		{
			continue;
		}
		else
		{
			reverse_recursive(p);
		}
	}
}

/*
Arguments: NODE pointer
Return Type: void
Functionality: Prints the names in each linked list in reverse order
*/
void backwards_recursive(char *p)
{
	if(*p == '\0')
	{
		return;
	}
	backwards_recursive(p+1);
	printf("%c", *p);
	
}

/*
Arguments: None
Return Type: void
Functionality: loops through array of linked lists and calls recursive function: backwards_recursive
*/
void backwards()
{
	NODE *p;
        for(int i = 0; i < 4; i++)
        {
                p = stuff[i].head;
                if(p == NULL)
                {
                	continue;       
                }
                else
                {
                        while(p != NULL)
			{
				backwards_recursive(p->names);
				p = p->next;
				printf("\n");
			}
                }
        }

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
	pthread_mutex_lock(&mutex);	
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
	pthread_mutex_unlock(&mutex);
	return;
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
	pthread_mutex_lock(&mutex);
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
	pthread_mutex_unlock(&mutex);	
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
	pthread_mutex_lock(&mutex);
        
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
	pthread_mutex_unlock(&mutex);
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



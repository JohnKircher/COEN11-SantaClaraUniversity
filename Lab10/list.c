#include "global.h"

/*Arguments: None
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





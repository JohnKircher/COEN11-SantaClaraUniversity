#include "global.h"

pthread_mutex_t  mutex;
pthread_t thread;
LIST stuff[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

int main(int argc, char *argv[])
{
        
        if(argc < 4)
        {       
                printf("The file name(s) is missing\n");
                return 0;
        }
	int key = atoi(argv[3]);
	
        readFile(argv[1], (char)key);
        
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
                        writeFile(argv[1], (char)key);
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

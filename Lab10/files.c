#include "global.h"

/*
arguments: char *arg
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
Arguments: char *file
Return Type: void
Functionality: recieves information from file
*/
void readFile(char *file, char key)
{       
        FILE *fp;
	char *q;
	char buffer[200];
        NODE *p; 
        char s[] = " ";
        int d = 0;
        if((fp = fopen(file, "r")) == NULL)
        {       
                printf("Cannot open file\n");
                return;
        }
        while(fgets(buffer, 200, fp) != NULL)
        {       
         	 q = buffer;
		 while(*q != '\0')
		 {
		 	*q ^= key;
			q++;
		 }
		 sscanf(buffer, "%s\t\t%d\n", s, &d);      	
		 insert(s, d);
		 //printf("%s\t%d\n", s, d);
        }
        fclose(fp);
        return;
}

/*
Arguments: char *file
Return Type: void
Functionality: writes information to the file
*/
void writeFile(char *file, char key)
{       
        char buffer[200];
	char *q;
	FILE *fp; 
        pthread_mutex_lock(&mutex);     
        if((fp = fopen(file, "w")) == NULL)
        {       
                printf("Cannot open file\n");
                return;
        }
        NODE *p;
        for(int i = 0; i < 4; i++)
        {       
                p = stuff[i].head;
                while(p != NULL)
                {       
			
                        sprintf(buffer, "%s\t\t%d\n", p->names, p->size);
			q = buffer;
			while(*q != '\0')
			{
				*q ^= key;
				q++;
			}
			fprintf(fp, "%s\n", buffer);
                        p=p->next;
                }
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        return;
}

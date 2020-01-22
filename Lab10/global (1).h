
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

extern LIST stuff[4];

void *auto_save(void *argc);
void readBinary(char *argc);
void reverse_recursive(NODE *p);
void reverse();
void backwards_recursive(char *p);
void backwards();
void readFile(char *file, char key);
void writeFile(char *file, char key);
void insert(char *name, int number);
int check_duplicate(char s[]);
void delete();
void show();
void search_size();
void quit_recursive(NODE *p);
void quit();

extern pthread_mutex_t  mutex;
extern pthread_t thread;

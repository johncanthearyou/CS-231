//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

//Create API for stack ADT
//    Main program using stack will not see implementation
//    Type of item in stack is determinded via include statement

#include <stdio.h>
#include <stdlib.h>

//typedef char dataType;
typedef double dataType;

#define BAD_EXIT 1

typedef struct node {
    struct node *next;
    dataType data;
} nodeType;

typedef struct stackHeader {
    struct node *top;
    struct node *bottom;
} stackType;

stackType* create();
int isEmpty( stackType * );
stackType* push( dataType, stackType * );
nodeType* peek( stackType * );
nodeType* pop( stackType * );
stackType* destroy( stackType ** );
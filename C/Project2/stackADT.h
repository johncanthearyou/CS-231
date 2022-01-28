//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

//Create API for stack ADT
//    Main program using stack will not see implementation
//    Type of item in stack is determinded via include statement

#include <stdio.h>
#include <stdlib.h>

typedef char dataType;
//typedef double dataType;

//Defines the 'objects' (structs) that the stack will contain
typedef struct node {
    struct node *next;
    dataType data;
} nodeType;

//Defines the 'object' (struct) that represents the stack itself
typedef struct stackHeader {
    struct node *top;
    struct node *bottom;
} stackType;

//Header functions for the stack.c file to implement
//See stack.c for further documentation
stackType* create();
int isEmpty( stackType * );
stackType* push( dataType, stackType * );
nodeType* peek( stackType * );
nodeType* pop( stackType * );
stackType* destroy( stackType ** );
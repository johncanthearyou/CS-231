//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

//TODO: Document file

#include "stackADT.h"

#define BAD_EXIT 1

//TODO: Document...
stackType* create() {
    stackType *newStack;
    newStack = (stackType *) malloc( sizeof(stackType) );
    if( !(newStack==NULL) ) {
        newStack -> top = NULL;
        newStack -> bottom = NULL;
    }
    return newStack;
}

//TODO: Document...
int isEmpty( stackType *stack ) {
    if( stack -> bottom == NULL ) { return 1; }
    return 0;
}

//TODO: Document...
stackType* push( dataType data, stackType *stack ) {
    if( stack==NULL ) { 
        fprintf(stderr, "Error: cannot push to null stack.\n");
        exit(BAD_EXIT);
    }
    
    nodeType *newNode = (nodeType *) malloc( sizeof(nodeType) );
    newNode -> data = data;
    if( isEmpty(stack) ) {
        newNode -> next = NULL;
        stack -> bottom = newNode;
    } else {
        newNode -> next = (stack -> top);
    }
    stack -> top = newNode;
    return stack;
}

//TODO: Document...
nodeType* peek( stackType *stack ) {
    if( stack==NULL ) { 
        fprintf(stderr, "Error! cannot peek at null stack.\n");
        exit(BAD_EXIT);
    }

    if( isEmpty(stack) ) { 
        fprintf(stderr, "Error! cannot peek at empty stack.\n");
        return NULL; 
    }
    return (stack -> top);
}

//TODO: Document...
nodeType* pop( stackType *stack ) {
    if( stack==NULL ) { 
        fprintf(stderr, "Error! cannot pop from null stack.\n");
        exit(BAD_EXIT);
    }

    if( isEmpty(stack) ) {
        fprintf(stderr, "Error! cannot pop from empty stack.\n");
        return NULL;
    } else {
        nodeType *poppedNode = stack -> top;
        stack -> top = (stack -> top) -> next;
        if( (stack -> top)==NULL ) { stack -> bottom = NULL; }

        free( (void *) poppedNode);
        return poppedNode;
    }
}

//TODO: Document...
stackType* destroy( stackType **stack ) {
    nodeType *currNode, *nextNode;
    if( !isEmpty(*stack) ) {
        currNode = (*stack) -> top;
        nextNode = currNode -> next;
        while( nextNode!=NULL ) {
            free( (void *) currNode );
            currNode = nextNode;
            nextNode = nextNode -> next;
        }
        free( (void *) currNode );
    }

    free( (void *) *stack );
    *stack = NULL;
    return *stack; 
}
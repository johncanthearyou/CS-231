//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022


//This imported file is where the data type for the stack nodes is defined
#include "stackADT.h"

//This function creates a new stack data structure with no elements, 
//  allocating the memory requred. Both the 'top' and 'bottom' elements
//  are set to null by default. The data type that the nodes contain are
//  defined on lines 13 or 14 of stackADT.h in the directory
//Inputs: None
//Outputs: pointer to stackType, the stack that was created
stackType* create() {
    stackType *newStack;
    newStack = (stackType *) malloc( sizeof(stackType) );
    if( !(newStack==NULL) ) {
        //Init top and bottom elements to NULL
        newStack -> top = NULL;
        newStack -> bottom = NULL;
    }
    return newStack;
}

//This function finds if the passed stack is empty by seing if the 
//  'bottom' node is null, if it is, the stack must be empty
//Inputs: pointer to stackType, the stack to be checked for emptiness
//Outputs: int (boolean) 1 if the stack is empty
//                       0 if the stack is NOT empty
int isEmpty( stackType *stack ) {
    if( stack -> bottom == NULL ) { return 1; }
    return 0;
}

//This function adds a new node to the top of the stack, allocating
//  the memory for each element
//Inputs: dataType, the data of the node to be added
//          (as defined in line 13 or 14 of stackADT.h)
//        stackType, the stack to which we will add the data
//Outputs: pointer to stackType, the updated stack
stackType* push( dataType data, stackType *stack ) {
    if( stack==NULL ) { 
        fprintf(stderr, "ERROR: cannot push to null stack.\n");
        return NULL;
    }
    
    nodeType *newNode = (nodeType *) malloc( sizeof(nodeType) );
    newNode -> data = data;
    if( isEmpty(stack) ) {
        newNode -> next = NULL; //There is no other node to point to
        stack -> bottom = newNode; //Set the 'bottom' node
    } else {
        //Point the new node to the old top of the stack
        newNode -> next = (stack -> top);
    }
    stack -> top = newNode; //Update the top of the stack
    return stack;
}

//This fuction gets the top node of the stack without 
//  deleting it from the stack
//Inputs: pointer to stackType, the stack from which we want the top node
//Outputs: pointer to nodeType, the top node of the stack
nodeType* peek( stackType *stack ) {
    if( stack==NULL ) {
        fprintf(stderr, "ERROR! cannot peek at null stack.\n");
        return NULL;
    } else if( isEmpty(stack) ) { 
        fprintf(stderr, "ERROR! cannot peek at empty stack.\n");
        return NULL; 
    }

    return (stack -> top);
}

//This function gets the top node of the stack, 
//  deleting the node from the stack and deallocating the memory of the node
//Inputs: pointer to stackType, the stack from which top node will be popped
//Outputs: pointer to nodeType, the (former) top node of the stack
nodeType* pop( stackType *stack ) {
    if( stack==NULL ) { 
        fprintf(stderr, "ERROR! cannot pop from null stack.\n");
        return NULL;
    }else if( isEmpty(stack) ) {
        fprintf(stderr, "ERROR! cannot pop from empty stack.\n");
        return NULL;
    }

    nodeType *poppedNode = stack -> top;
    stack -> top = (stack -> top) -> next; //update the top node to the next node
    if( (stack -> top)==NULL ) { 
        //We are popping the only node, set the 'bottom' node to NULL
        stack -> bottom = NULL; 
    }

    free( (void *) poppedNode); //deallocate the memory for the popped node
    return poppedNode;
}

//This function deletes an entire stack data structure with no elements, 
//  deallocating the memory. Each of the nodes are deallocated as well.
//Inputs: pointer to pointer to stackType, the stack to delete
//Outputs: NULL, the stack has been deleted
stackType* destroy( stackType **stack ) {
    nodeType *currNode, *nextNode;

    //Go through and deallocate each node of the stack
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

    //Deallocate memory for the whole stack
    free( (void *) *stack );
    *stack = NULL;
    return *stack; 
}
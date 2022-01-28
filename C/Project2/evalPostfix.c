//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

//TODO: File overview

#include <stdio.h>
#include <stdlib.h>
#include "stack.c"

//TODO: Document...
int isOperator( char character ) {
    return ( character=='+' ||
             character=='-' || 
             character=='*' || 
             character=='/' 
           );
}

//TODO: Document
dataType combineOperands( dataType op1, dataType op2, char operator ) {
    switch( operator ) {
        case '+':
            return op1+op2;
        case '-':
            return op1-op2;
        case '*':
            return op1*op2;
        default:
            return op1/op2;
    }
}

//Function to compute the index of a given char in a string
//Inputs: pointer to char array, the string we will search
//        char, the character for which we are trying to find the index
//Outputs: int, the length of the string
int findChar( char *str, char c ) {
    int idx = 0;
    while( *str != c ) {
        if( *str == '\0' ) { return -1; } //char c was not found
        idx++;
        str++;
    }
    return idx;
}

//Function to compute the index of the first newline character in a string
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string OR 
//              -1 if it is not found
int findNewLine( char *str ) { return findChar( str, '\n' ); }

//TODO: Document...
int main( int argc, char *argv[] ) {
    FILE *inputFile, *outputFile;
    int maxChars = 80;
    char tmpLine[maxChars+2];

    stackType *stack = create();
    dataType op1, op2;

    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        printf( "ERROR! Unable to open the input file: %s\n", argv[1] );
        exit(BAD_EXIT); //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    //Read input file, proccess strings, and write to output
    int isFirstLine = 1;
    while( fgets(tmpLine, maxChars+1, inputFile)!=NULL ) {
        if( !isFirstLine ) { fputs( "\n", outputFile ); }
        else { isFirstLine--; } //First line, switch flag

        tmpLine[findNewLine(tmpLine)] = '\0';
        for( int i=0; tmpLine[i]!='\0'; i++ ) {
            if( tmpLine[i]==' ' ) { continue; }
            else if( isOperator(tmpLine[i]) ) {
                op1 = pop( stack ) -> data;
                op2 = pop( stack ) -> data;
                push( combineOperands(op1, op2, tmpLine[i]), stack );
            } else {
                push( tmpLine[i]-48, stack );
            }
        }

        fprintf( outputFile, "%s = %f", tmpLine, pop( stack ) -> data );
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
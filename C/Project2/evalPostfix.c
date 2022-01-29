//atof

//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

#define BAD_EXIT -1

//This function takes a character and determines if it is 
//  one of the 4 basic arithmetic operators
//Inputs: char, the character to be checked
//Outputs: int (boolean) 1 if the character is an operator
//                       0 if the character is NOT an operator
int isOperator( char character ) {
    return ( character=='+' ||
             character=='-' || 
             character=='*' || 
             character=='/' 
           );
}

//This function takes 2 operands and determines how they should be combined
//  with the 3rd parameter, the operator
//NOTE: It is assumed that the operator will be one of the 4 arithmetic operators,
//  otherwise, it will end the program
//Inputs: dataType, the first operand to be combined arithemetically
//        dataType, the second operand to be combined arithemetically
//        char, the character which will determine how the operands 
//          will be arithmetically combined
//Outputs: dataType, the arithmetic combination of the two operands based
//           on the input operator character
dataType combineOperands( dataType op1, dataType op2, char operator ) {
    switch( operator ) {
        case '+': return op1+op2;
        case '-': return op1-op2;
        case '*': return op1*op2;
        case '/': return op1/op2;
        default: 
            fprintf(stderr, "Invalid operator passed to 'combineOperands'" );
            exit(BAD_EXIT);
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

//Function to compute the length of a given string by searching for '\0'
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string
int length( char *str ) { return findChar( str, '\0' ); }

//Function to compute the index of the first newline character in a string
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string OR 
//              -1 if it is not found
int findNewLine( char *str ) { return findChar( str, '\n' ); }

//This program takes an input file, changes the case of all
//    letters in the input file, and prints it to an output file
//Inputs: int, the number of arguments passed to the program
//        pointer to array of strings, the name of the input
//                                       and output files, respectively
//Outputs: int, 0 for success
//              May be terminated early by exit() call
int main( int argc, char *argv[] ) {
    FILE *inputFile, *outputFile;
    int maxChars = 80;
    char tmpLine[maxChars+2];
    char *tmpLinePtr;
    int newLineIdx;

    stackType *stack = create();
    dataType op1, op2, result;

    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        fprintf(stderr, "Unable to open the input file: %s\n", argv[1] );
        exit(BAD_EXIT); //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    //Read input file, proccess strings, and write to output
    int isFirstLine = 1;
    while( fgets(tmpLine, maxChars+2, inputFile)!=NULL ) {
        if( !isFirstLine ) { fprintf( outputFile, "\n" ); }
        else { isFirstLine--; } //First line, switch flag

        //replace '\n' with '\0' to end string there
        newLineIdx = findNewLine( tmpLine );
        if( newLineIdx!=-1 ) tmpLine[newLineIdx] = '\0';
        if( length(tmpLine)>maxChars ) {
            fprintf( outputFile, "ERROR: Line is too long. Exiting program." );
            exit(BAD_EXIT);
        }

        tmpLinePtr = tmpLine;
        while( *tmpLinePtr!='\0' ) {
            if( *tmpLinePtr==' ' || *tmpLinePtr=='\n' || *tmpLinePtr=='\t' ) { 
                //This is a whitespace, skip to next char
                tmpLinePtr++;
                continue; 
            } else if( isOperator(*tmpLinePtr) ) {
                if( isEmpty(stack) || (peek(stack) -> next)==NULL ) {
                    //There aren't enough operands!
                    fprintf( outputFile, 
                             "ERROR! \"%s\" has invalid syntax. Exiting.",
                             argv[1]
                           );
                    exit(BAD_EXIT);
                }
                //Found an operator, combine last two nodes on stack
                op2 = pop( stack ) -> data; //extract data from popped node
                op1 = pop( stack ) -> data; //extract data from popped node
                result = combineOperands(op1, op2, *tmpLinePtr);
                push( result, stack );
            } else if( (*tmpLinePtr>='0' && *tmpLinePtr<='9') 
                            || *tmpLinePtr=='.' ) {
                //This is a number, read it as a double and push to stack
                result = strtod( tmpLinePtr, &tmpLinePtr );
                push( result, stack );
            } else {
                //Did not get a space, number, or operator, exit program
                fprintf( outputFile, 
                         "ERROR! \"%s\" has invalid characters. Exiting.\n",
                         argv[1]
                       );
                exit(BAD_EXIT);
            }

            tmpLinePtr++;
        }

        result = pop( stack ) -> data; //The overall result for the line
        fprintf( outputFile, "%s = %f", tmpLine, result );
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
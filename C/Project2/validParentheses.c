//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <string.h>
#include "stackADT.h"

#define BAD_EXIT -1

//This function takes a character and determines if it is 
//  a valid opening parenthesis
//Inputs: char, the character to check
//Outputs, int (boolean), 1 if the char is a valid opening parenthesis
//                        0 if the cahr is NOT a valid opening parenthesis
int isOpening( char character ) { 
    return character=='(' || character=='[' || character=='{'; 
}

//This function takes a character and determines if it is 
//  a valid closing parenthesis
//Inputs: char, the character to check
//Outputs, int (boolean), 1 if the char is a valid closing parenthesis
//                        0 if the cahr is NOT a valid closing parenthesis
int isClosing( char character ) { 
    return character==')' || character==']' || character=='}';  
}

//This functinon takes a character and checks if the top node of a given stack
//  is the corresponding opening parenthesis
//Inputs: char, the character (loosely assumed to be a closing parenthesis) to
//                be checked for association with the top node of a stack
//        pointer to stackType, the stack for which the top node will be
//                                checked for association with a closing
//                                parenthesis char
//Outputs: int (boolean), 1 if the char and stack are matching parentheses chars
//                        0 if the char and stack are NOT matching parentheses chars
int arePartners( char character, stackType *stack ) {
    if( isEmpty(stack) ) { return 0; }
    else if( character==')' ) { return (peek(stack) -> data)=='('; }
    else if(  character==']'  ) { return (peek(stack) -> data)=='['; }
    else if(  character=='}'  ) { return (peek(stack) -> data)=='{'; }
    return 0;
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

//This funtion takes a string and determines if it follows 
//  proper parenthetical punctuation
//Inputs: pointer to char array, the string to process and determine validity
//Outputs: int (boolean), 1 if the string is valid
//                        0 if the string is NOT valid
int isValid(char *str) {
    if( str==NULL ) {
        fprintf(stderr, "ERROR: cannot evaluate NULL string.\n");
        return 0;
    }

    stackType *stack = create();
    for(int i = 0; i < strlen(str); i++) {
        if( isOpening(str[i]) ) {
            //Found opening parenthesis, push to stack
            push( str[i], stack );
        } else if( isClosing(str[i]) ) {
            //Found closing parenthesis...
            if( arePartners(str[i], stack) ) {
                //Closing parenthesis matches stack's top node, 
                //  pop opening parenthesis from stack
                pop(stack);
            } else { 
                //Closing parenthesis doesn't match stack's top node
                return 0;
            }
        }
    }
    if( !isEmpty(stack) ) {
        //Stack isn't empty, this means we have unmatched opening parenthesis 
        return 0; 
    }

    destroy( &stack ); 
    return 1; //If we got this far, the string must be valid
}

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
    int newLineIdx;

    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        printf( "ERROR! Unable to open the input file: %s\n", argv[1] );
        exit(BAD_EXIT); //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    //Read input file, proccess strings, and write to output
    for( int lineNum=1; fgets(tmpLine, maxChars+2, inputFile)!=NULL; lineNum++ ) {
        if( !(lineNum==1) ) { fprintf( outputFile, "\n" ); }

        if( length(tmpLine)==(maxChars+1) && tmpLine[maxChars]!='\n' ) {
            fprintf( outputFile,
                     "ERROR: Line #%d is too long. Exiting program.",
                     lineNum
                   );
            exit(BAD_EXIT);
        }

        fprintf( outputFile, "%s ->", tmpLine );
        if( isValid(tmpLine) ) { 
            fprintf( outputFile, "VALID PARENTHESIZATION" ); 
        } else {
            fprintf( outputFile, "INVALID PARENTHESIZATION" ); 
        }
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <string.h>
#include "stack.c"

#define BAD_EXIT 1

//TODO: Document...
int isOpening( char character ) { 
    return character=='(' || character=='[' || character=='{'; 
}

//TODO: Document...
int isClosing( char character ) { 
    return character==')' || character==']' || character=='}';  
}

//TODO: Document...
int arePartners( char character, stackType *stack ) {
    if( isEmpty(stack) ) { return 0; }
    else if( character==')' ) { return (peek(stack) -> data)=='('; }
    else if(  character==']'  ) { return (peek(stack) -> data)=='['; }
    else if(  character=='}'  ) { return (peek(stack) -> data)=='{'; }
    return 0;
}

//TODO: Document...
int isValid(char *str) {
    if( str==NULL ) {
        fprintf(stderr, "Error: cannot evaluate NULL string.\n");
        return 0;
    }

    stackType *stack = create();
    for(int i = 0; i < strlen(str); i++) {
        if( isOpening(str[i]) ) {
            push( str[i], stack );
        } else if( isClosing(str[i]) ) {
            if( arePartners(str[i], stack) ) {
                pop(stack);
            } else { 
                return 0;
            }
        }
    }
    if( !isEmpty(stack) ) { return 0; }

    destroy( &stack );
    return 1;
}

//TODO: Document...
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
    for( int lineNum=0; fgets(tmpLine, maxChars+1, inputFile)!=NULL; lineNum++ ) {
        if( !(lineNum==0) ) { fputs( "\n", outputFile ); }

        if( isValid(tmpLine) ) { 
            fprintf( outputFile, 
                     "Line #%d has valid parenthesization", 
                      lineNum 
                   ); 
        } else {
            fprintf( outputFile, 
                     "Line #%d DOESN'T have valid parenthesization",
                     lineNum 
                   ); 
        }
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
// David Vineyard, John Stockton
// Dr. Vineyard
// CS-231
// Winter 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 80

//This function takes a file stream and updates it to point
//    at the next new line in the file
//Inputs: pointer to File, the file for which we want to skip to a new line
//Outputs: none
void clearLine(FILE *file) {
    char c = getc(file);
    while (c != '\n') { c = getc(file); }
}

//This function adds a string to a string array, dynamically reallocating the 
//    size of the array once it fills up 
//Inputs: int, the index at which we want to insert the string 
//        into the string array
//        pointer to char pointer, the array into which we want to insert a string
//        pointer to char, the string we want to insert into the array
//Outputs: None
void addToArray(int index, char **arrayPtr, char *line) {
    int len = strlen( line );
    if ( len==(MAX_CHARS-1) && line[MAX_CHARS-1]!='\n' ) {
        *( arrayPtr+index ) = malloc( MAX_CHARS );
        line[MAX_CHARS-1] = '\0';
        fprintf( stderr, "%s\n", line );
        strncpy( *(arrayPtr+index), line, MAX_CHARS );
        clearLine( stdin ); // remove remainder of input line
    } else {
        char *linePtr = strchr(line, '\n');
        if ( linePtr!=NULL ) {  *linePtr = '\0'; }
        *( arrayPtr+index ) = malloc( strlen(line)+1 );
        strncpy( *(arrayPtr+index), line, MAX_CHARS-1 );
    }
}

//Main will look for words from stdin, each separated by a new line
//    Then, it uses a dynamic array to load the strings
//    Finally, it will print the words (as they are given), in
//    reverse order (LIFO) to stdout
//Inputs: None
//Outputs: None
int main() {
    int strIdx = 0;
    int currSize = 10; //This is the initial size of the string array

    char inputLine[MAX_CHARS+1];
    //Allocate enough size for 10 char pointers
    char **strArrayPtr = malloc( currSize*sizeof(char *) ); 

    char *tmpLine;
    tmpLine = fgets(inputLine, MAX_CHARS, stdin);
    while ( tmpLine!=NULL ) {
        if ( strIdx==currSize ) {
            //We've reached the max size for the string array
            //    Reallocate an array with 10 more elements, then insert
            currSize += 10;
            strArrayPtr = realloc( strArrayPtr, currSize*sizeof(char *) );
        }
        addToArray( strIdx, strArrayPtr, inputLine );

        strIdx++;
        tmpLine = fgets( inputLine, MAX_CHARS, stdin );
    }

    //Print the contents of the array of strings in reverse order
    for( int i=(strIdx-1); i>=0; i-- ) {
        fprintf( stdout, "%s\n", *(strArrayPtr+i) );
    }
}
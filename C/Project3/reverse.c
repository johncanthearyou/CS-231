// John Stockton
// Dr. Vineyard
// CS-231
// Winter 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 20

void clearLine(FILE *file) {
    char c = getc(file);
    while (c != '\n') { c = getc(file); }
}

void addToArray(int index, char **arrayPtr, char *line) {
    int len = strlen( line );
    if ( len==(MAX_LINE_SIZE-1) && line[MAX_LINE_SIZE-1]!='\n' ) {
        *( arrayPtr+index ) = malloc( MAX_LINE_SIZE );
        line[MAX_LINE_SIZE-1] = '\0';
        fprintf( stderr, "%s\n", line );
        strncpy( *(arrayPtr+index), line, MAX_LINE_SIZE );
        clearLine( stdin ); // remove remainder of input line
    } else {
        char *linePtr = strchr(line, '\n');
        if ( linePtr!=NULL ) {  *linePtr = '\0'; }
        *( arrayPtr+index ) = malloc( strlen(line)+1 );
        strncpy( *(arrayPtr+index), line, MAX_LINE_SIZE-1);
    }
}

//TODO: Document...
int main() {
    int strIdx = 0;
    int currSize = 10;

    char inputLine[MAX_LINE_SIZE];
    char **strArrayPtr = malloc( currSize*sizeof(char *) );

    char *tmpLine;
    tmpLine = fgets(inputLine, MAX_LINE_SIZE, stdin);

    while ( tmpLine!=NULL ) {
        if ( strIdx==currSize ) {
            currSize += 10;
            strArrayPtr = realloc( strArrayPtr, currSize*sizeof(char *) );
        }
        addToArray( strIdx, strArrayPtr, inputLine );

        strIdx++;
        tmpLine = fgets( inputLine, MAX_LINE_SIZE, stdin );
    }

    for( int i=(strIdx-1); i>=0; i-- ) {
        fprintf( stdout, "%s\n", *(strArrayPtr+i) );
    }
}
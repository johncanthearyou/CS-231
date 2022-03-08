//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 80

//Function to compute the length of a string, terminating on '\n' or '\0'
//Inputs: pointer to char array, the string on which we will compute length
//Outputs: int, the length of the string
int len( char *str ) {
    int idx = 0;
    while( *str != '\n' && *str != '\0' ) {
        idx++;
        str++;
    }
    return idx;
}

//Main takes 1 argument, the length of the words we want to keep
//    It reads words from stdin, and discards them if they do not
//    match the length given to the file, then prints all the words
//    of a specific length to stdout
int main( int argc, char *argv[] ) {
    int length = atof(argv[1]);
    char tmpString[MAX_CHARS+2];

    while( fgets(tmpString, MAX_CHARS+2, stdin) ) {
        if( len(tmpString)==length ) {
            printf( "%s", tmpString );
        }
    }

}
//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>
#include <stdlib.h>

//Function to compute the length of a string, terminating on '\n' or '\0'
//Inputs: pointer to char array, the string on which we will compute length
//Outputs: int, the length of the string
int length( char *str ) {
    int idx = 0;
    while( *str != '\n' && *str != '\0' ) {
        idx++;
        str++;
    }
    return idx;
}

//TODO: Document...
int main( int argc, char *argv[] ) {
    int maxLength = atof(argv[1]);
    char tmpString[81];

    while( fgets(tmpString, 81, stdin) ) {
        if( length(tmpString)==maxLength ) {
            printf( "%s", tmpString );
        }
    }

}
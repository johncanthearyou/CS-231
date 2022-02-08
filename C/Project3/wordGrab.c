//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>

#define INIT 3
#define WORD 1
#define DELIMITER 2

//TODO: Document...
int isLetter( char letter ) {
    return ( (letter>='A' && letter<='Z') || (letter>='a' && letter<='z') );
}

//TODO: Document...
int main( int argc, char *argv[] ) {
    FILE *input = fopen( argv[1], "r" );
    int state = INIT;

    char tmpChar = fgetc(input);
    while( tmpChar!=EOF ) {
        switch( isLetter(tmpChar) ) {
            case 1:
                printf( "%c", tmpChar );
                state = WORD;
                break;
            case 0:
                if( state==WORD ) { printf( "\n" ); }
                state = DELIMITER;
                break;
        }
        tmpChar = fgetc(input);
    }
}
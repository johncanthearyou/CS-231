//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>

#define INIT 3
#define WORD 1
#define DELIMITER 2

//This function takes a char and determines if it is a letter
//Inputs: char, the letter to check
//Outputs: int (boolean), 1 if given char is a letter
//                        0 if given char is NOT a letter
int isLetter( char letter ) {
    return ( (letter>='A' && letter<='Z') || (letter>='a' && letter<='z') );
}

//Main will take 1 argument, the name of the file from which to read
//    It then parses the file for words reading one char at a time
//    delimiting with any non-letter character, each of these parsed
//    words is then printed to stdout
int main( int argc, char *argv[] ) {
    FILE *input = fopen( argv[1], "r" );
    int state = INIT;

    char tmpChar;
    while( (tmpChar=fgetc(input))!=EOF ) {
        if( isLetter(tmpChar) ) {
            state = WORD;
            printf( "%c", tmpChar );
        } else {
            if( state==WORD ) { printf( "\n" ); }
            state = DELIMITER;
        }
    }
}
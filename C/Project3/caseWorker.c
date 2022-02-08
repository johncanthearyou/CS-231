//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>

//TODO: Document...
int isVowelUpper( char letter ) {
    switch(letter) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
    }
    return 0;
}

//TODO: Document...
int isConsonantLower( char letter ) {
    if( letter>='a' && letter<='z' ) {
        switch(letter) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return 0;
        }
        return 1;   
    }
    return 0;
}

//TODO: Document...
int main( int argc, char *argv[] ) {
    FILE *output = fopen( argv[1], "w" );

    char tmpChar = fgetc(stdin);
    while( tmpChar!=EOF ) {
        if( isVowelUpper(tmpChar) ) { tmpChar += 32; }
        else if( isConsonantLower(tmpChar) ) { tmpChar -= 32; }
        fputc( tmpChar, output );
        tmpChar = fgetc(stdin);
    }
}
//John Stockton
//Dr. Vineyard
//CS-231
//Winter 2022

#include <stdio.h>

#define CASE_OFFSET 32

//This function takes a character and determines if it is an uppercase vowel
//Inputs: char, the character to check
//OutputsL int (boolean), 1 if character is an uppercase vowel
//                        0 if character is NOT an uppercase vowel
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

//This function takes a character and determines if it is a lowercase consonant
//Inputs: char, the character to check
//OutputsL int (boolean), 1 if character is a lowercase consonant
//                        0 if character is NOT a lowercase consonant
int isConsonantLower( char letter ) {
    if( letter>='a' && letter<='z' ) {
        //char is a lowercase letter
        switch(letter) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                //we found a lowercase vowel, return false
                return 0;
        }
        //lowercase letter is not a vowel, it must be a consonant
        return 1;   
    }
    return 0;
}

//Main takes one argument, the name of the file to write to
//    It will read words in from stdin, convert all vowels to lowercase
//    and all consonants to uppercase, then print those words to the file given
int main( int argc, char *argv[] ) {
    FILE *output = fopen( argv[1], "w" );

    char tmpChar;
    while( (tmpChar=fgetc(stdin))!=EOF ) {
        if( isVowelUpper(tmpChar) ) { tmpChar += CASE_OFFSET; }
        else if( isConsonantLower(tmpChar) ) { tmpChar -= CASE_OFFSET; }
        fputc( tmpChar, output );
    }
}
//John Stockton
//CS-231
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <string.h>

//Function to check if a given character is an uppercase letter
//Inputs:  char, the character to be checked
//Outputs: int, 0 if character is uppercase letter
//              1 if character is NOT uppercase (including non-letters)
int isUpper( char letter ) {
    return (letter>='A' && letter<='Z');
} 

//Function to check if a given character is a lowercase letter
//Inputs:  char, the character to be checked
//Outputs: int, 0 if character is lowercase letter
//              1 if character is NOT lowercase (including non-letters)
int isLower( char letter ) {
    return (letter>='a' && letter<='z');
} 

//Function to compute the length of a given string (char[])
//    by counting all the chars up to the '\0' char
//Inputs:  char[], a string for which the length will be computed
//Outputs: int, the length of the input string
int length( char s[] ) {
    int count = 0;
    for( int i=0; s[i]!='\0'; i++ ) { count++; }
    return count;
}

//Function (in-place) to switch the case of all 
//    constituent letters in a given string
//Inputs:  char array, the string to be case-inverted
//Outputs: pointer to char array, processed string  and case-inverted 
char* switchCase( char str[] ) {
    int strLength = length(str);

    for( int i=0; i<strLength; i++ ) {
        if( isUpper( str[i] ) ) { 
            //letter is uppercase, modify ASCII value to lowercase letter    
            str[i] += 32; 
        } else if( isLower( str[i] ) ) { 
            //letter is lowercase, modify ASCII value to uppercase letter
            str[i] -= 32; 
        }
    }

    return str;
}

int main( int argc, char * argv[] ) {
    //Init input and output files
    FILE *inputFile, *outputFile;
    inputFile = fopen( argv[1], "r" ); //read only
    outputFile = fopen( argv[2], "w"); //write only
    
    //TODO: Move on to new line for lines >=100
    //define the maximum length of a line that can be read
    int maxLineSize = 101;
    char tmpLine[maxLineSize];
    while( fgets(tmpLine, maxLineSize, inputFile)!=NULL ) {
        switchCase(tmpLine);
        fputs( tmpLine, outputFile );
    }

    fclose( inputFile );
    fclose( outputFile );
}
//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>

//Function to check if a given character is an uppercase letter
//Inputs:  char, the character to be checked
//Outputs: int (boolean), 1 if character is uppercase letter
//                        0 if character is NOT uppercase letter
int isUpper( char letter ) { return (letter>='A' && letter<='Z'); } 

//Function to check if a given character is a lowercase letter
//Inputs:  char, the character to be checked
//Outputs: int (boolean), 1 if character is lowercase letter
//                        0 if character is NOT lowercase letter
int isLower( char letter ) { return (letter>='a' && letter<='z'); }

//Function to compute the index of a given char in a string
//Inputs: pointer to char array, the string we will search
//        char, the character for which we are trying to find the index
//Outputs: int, the length of the string
int findChar( char *str, char c ) {
    int idx = 0;
    while( *str != c ) {
        if( *str == '\0' ) { return -1; } //char c was not found
        idx++;
        str++;
    }
    return idx;
}

//Function to compute the length of a given string by searching for '\0'
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string
int length( char *str ) { return findChar( str, '\0' ); }

//Function to compute the index of the first newline character in a string
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string OR 
//              -1 if it is not found
int findNewLine( char *str ) { return findChar( str, '\n' ); }

//Function (in-place) to switch the case of all letters
//    in a given string, leaving non-letters alone
//Inputs:  char array, the string to be case-inverted
//Outputs: pointer to char array, processed string
char* switchCase( char *str ) {
    while( *str != '\0' ) {
        if( isUpper(*str) ) { 
            //letter is uppercase, modify ASCII value to lowercase letter
            *str += 32; 
        } else if( isLower(*str) ) { 
            //letter is lowercase, modify ASCII value to uppercase letter
            *str -= 32; 
        }
        str++;
    }
    return str;
}

//This program takes an input file, changes the case of all
//    letters in the input file, and prints it to an output file
//Inputs: int, the number of arguments passed to the program
//        pointer to array of strings, the name of the input
//        and output files, respectively
//Outputs: int, 0 for success OR
//             -1 for failure
int main( int argc, char *argv[] ) {
    FILE *inputFile, *outputFile;
    int maxChars = 100;
    char tmpLine[maxChars+1];
    int newLineIdx;

    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        printf( "ERROR! Unable to open the input file: %s\n", argv[1] );
        return -1; //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    //Read input file, proccess strings, and write to output
    int isFirstLine = 1;
    while( fgets(tmpLine, maxChars+1, inputFile)!=NULL ) {
        if( !isFirstLine ) { fputs( "\n", outputFile ); }
        else { isFirstLine--; } //First line, switch flag

        newLineIdx = findNewLine(tmpLine); 
        if( newLineIdx==-1 ) {
            //Max line size reached, skip to next line in the file
            if( length(tmpLine)==maxChars ) {
                printf( "Max line size reached! Output will be truncated.\n");
            }
            fscanf(inputFile, "%*[^\n]"); //Skip up to '\n'
            fscanf(inputFile, "%*c");     //Skip '\n' itself          
        } else {
            //Replace '\n' with '\0'
            tmpLine[newLineIdx]='\0'; 
        }

        switchCase(tmpLine);
        fputs( tmpLine, outputFile ); //write processed string to output file
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
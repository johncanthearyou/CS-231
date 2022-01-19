//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>

//Function to check if a given character is an uppercase letter
//Inputs:  char, the character to be checked
//Outputs: int (boolean), 0 if character is uppercase letter
//                        1 if character is NOT uppercase letter
int isUpper( char letter ) { return (letter>='A' && letter<='Z'); } 

//Function to check if a given character is a lowercase letter
//Inputs:  char, the character to be checked
//Outputs: int (boolean), 0 if character is lowercase letter
//                        1 if character is NOT lowercase letter
int isLower( char letter ) { return (letter>='a' && letter<='z'); }

//Function to compute the length of a given string by searching for '\0'
//Inputs: pointer to char array, the for which we want to find length
//Outputs: int, the length of the string
int length( char *str ) {
    int length = 0;
    while( *str != '\0' ) {
        length++;
        str++;
    }
    return length;
}

//Function (in-place) to switch the case of all letters
//    in a given string, leaving non-letters alone
//Inputs:  char array, the string to be case-inverted
//Outputs: pointer to char array, processed string  and case-inverted
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

int main( int argc, char * argv[] ) {
    FILE *inputFile, *outputFile;
    //TODO: Should it be 100 +'\n' +'\0' (102)
    //      Or should it be 100 +'\0' (101) only
    int maxLineSize = 102; //
    char tmpLine[maxLineSize];

    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        printf( "ERROR! Unable to open the input file: %s\n", argv[1] );
        return -1; //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    //Read input file, proccess strings, and write to output
    while( fgets(tmpLine, maxLineSize, inputFile)!=NULL ) {
        if( length(tmpLine)==(maxLineSize-1) & tmpLine[maxLineSize-2]!='\n' ) {
            printf( "ERROR! Max length for a line exceeded! The line will be truncated.\n" );
            tmpLine[maxLineSize-2] = '\0';
            fscanf(inputFile, "%*[^\n]"); //Skip to next '\n' char, or EOF
        }
        
        switchCase(tmpLine);
        //Write the processed string to the output file
        fputs( tmpLine, outputFile );
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
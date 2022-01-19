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

//Function (in-place) to switch the case of all 
//    constituent letters in a given string
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
    return str; //Still the head of the string
}

int main( int argc, char * argv[] ) {
    //Variable Declarations
    FILE *inputFile, *outputFile;
    int maxLineSize = 101;
    char tmpLine[maxLineSize];
    //Init input and output files
    inputFile = fopen( argv[1], "r" ); //read only
    if( inputFile==NULL ) {
        printf( "ERROR! Unable to open the input file: %s\n", argv[1] );
        return -1; //Generic fail condition
    } else { outputFile = fopen( argv[2], "w"); } //write only

    while( fgets(tmpLine, maxLineSize, inputFile)!=NULL ) {
        //Check if the current line is too long
        if( length(tmpLine)==(maxLineSize-1) & tmpLine[maxLineSize-2]!='\n' ) {
            if( fscanf(inputFile, "%*[^\n]")==0 ) {
                printf( "%s\n", "Max length exceeded! The line will be truncated.");
                
            }
        }
        
        switchCase(tmpLine);
        //Write the processed string to the output file
        fputs( tmpLine, outputFile );
    }

    fclose( inputFile );
    fclose( outputFile );
    return 0;
}
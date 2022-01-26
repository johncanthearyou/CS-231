//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <string.h>

static char outputValue[40]; //Dangerous, global variable!

//outputValue is here to show the use of static storage type.
//The function fizzBuzz will place a string in outputValue each
//time it is called.

//Write the body of the function fizzBuzz.
//This will place the string Fizz in outputValue for multiples
//of 3, place the string Buzz in output value for multiples of 5,
//and will place the string FizzBuzz in outputValue for multiples of
//15.  Any other value stored in number will be copied as a string to
// outputValue.

//Use the function printf to change int number to a string
//version of the number to be placed in outputValue.
void fizzBuzz( int number ) {
	strcpy( outputValue, "" );

	if( (number%3)==0 ) { strncat( outputValue, "Fizz", 4 ); }
	if( (number%5)==0 ) { strncat( outputValue, "Buzz", 4 ); }
	
	if( strncmp( outputValue, "", 1 ) == 0 ) { 
		sprintf( outputValue, "%d", number ); 
	}
}


int main() {
	printf( "Automated Fizz Buzz\n" );
	printf( "Print the numbers from 1 to the input number,\n" );
	printf( "Replace multiples of 3 with Fizz, multiples of 5 with Buzz.\n" );
	printf( "Multiples of 15 will be replaced with FizzBuzz.\n" );
	printf( "Each output will be on its own line.\n\n" );

	printf( "How many numbers would you like to process? " );

	int lastVal;
	scanf( "%i", &lastVal );

	printf( "\nYour results are:\n\n" );

	for(int thisVal = 1; thisVal <= lastVal; thisVal++){
		fizzBuzz(thisVal);
		printf("%s\n", outputValue); 
	}
}
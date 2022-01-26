//John Stockton
//CS-231, Section 1
//Dr. Vineyard
//Winter 2022

#include <stdio.h>
#include <string.h>

static char outputValue[40]; //Dangerous, global variable!

//In-place function fizzBuzz takes an int and writes to 
//global variable outputValue:
//    "Fizz" if the int is divisible by 3
//    "Buzz" if the int is divisible by 5
//    "FizzBuzz" if the int is divisble by both 3 and 5 (15)
//Inputs: int, the number to be checked
//Outputs: void, no return value
void fizzBuzz( int number ) {
	strcpy( outputValue, "" );

	if( (number%3)==0 ) { strncat( outputValue, "Fizz", 4 ); }
	if( (number%5)==0 ) { strncat( outputValue, "Buzz", 4 ); }
	
	if( strncmp( outputValue, "", 1 ) == 0 ) { 
		sprintf( outputValue, "%d", number ); 
	}
}

//Function main implements and automated version of the 'FizzBuzz' game 
//  (see function 'fizzBuzz')
//  It asks the user how many numbers the program should evaluate from
//    1 to the user-given number. 
//  Then, prints to the console the appropriate response for a number 
//    from 1 to the user-given number.
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
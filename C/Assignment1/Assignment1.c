#include <stdio.h>

int main( void ) {
    float num1, num2;

    //read the first num from terminal
    printf( "Enter the first number> " );
    scanf( "%f", &num1 ); //Write to the memory address of num1

    //read the second num from terminal
    printf( "\nEnter the second number> " );
    scanf( "%f", &num2 ); //Write to the memory address of num2

    //Output the results
    printf( "\nValues: %f, %f\n", num1, num2 );
    printf( "\tSum: %f\n", num1+num2 );
    printf( "\tProduct: %f\n", num1*num2 );

    return 0;
}
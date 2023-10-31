/* 
 * test-atoi.c
 * This program shows how numbers
 * stored as strings can be converted to
 * numeric values using the atoi functions
 * 
 * the argument format 
 * [whitespace][sign][digits]
 * whitespace : '\t' or ' '
 * sign : '+' or '-'
 * digits : one or more numbers
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main( void ) {
    char *str = NULL;
    int value = 0;

    // An example of the atoi function.
    str = " -2309 ";
    value = atoi( str );
    printf( "Function: atoi( \"%s\" ) = %d\n", str, value );

    // Another example of the atoi function.
    str = "31412764";
    value = atoi( str );
    printf( "Function: atoi( \"%s\" ) = %d\n", str, value );

    // Another example of the atoi function
    // with an overflow condition occurring.
    str = "374891728937413438912328";
    value = atoi( str );
    printf( "Function: atoi( \"%s\" ) = %d\n", str, value );
    if (errno == ERANGE) {
        printf("Overflow condition occurring.\n");
    }
}

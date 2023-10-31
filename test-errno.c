/*
 * The C library Macro - errno
 *
 * Description 
 * The C library macro extern int errno 
 * is set by system call and some library function 
 * in the event of an error to indicate if anything went wrong.
 *
 * Declaration
 * Following is the declaration for errno macro
 * extern int errno
 *
 * Parameters
 * NA
 *
 * Return Value
 * NA
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main() {
    FILE *fp;
    fp = fopen( "file.txt", "r" );
    if (fp == NULL) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } else {
        fclose(fp);
    }

    return(0);
}

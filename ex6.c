#include <stdio.h>

int main(int argc, char *argv[]) {
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    // Process terminating with default action of signal 11 (SIGSEGV)
    // Cause : Stack Overflow 
    // initial is char, %s expects char[] is end of '\0'
    // printf function access not with mapped region. 
//    printf("My whole name is %s %c. %s.\n",
//            initial, first_name, last_name);
    printf("%s", "");

    return(0);
}

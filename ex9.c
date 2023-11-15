#include <stdio.h>

int main(int argc, char *argv[]) {
    int numbers[4] = { 'a', 'b', 'c', 'd' };
    char *name = "aaaa";

    //name[3] = 'A';

    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 'Z';
    numbers[1] = 'e';
    numbers[2] = 'd';
    numbers[3] = 4;

    // setup the name
/*    name[0] = 0x5a;
    name[1] = 0x65;
    name[2] = 0x64;
    name[3] = '\0';
*/
    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    // print the name like a string
    printf("name: %s\n", name);

//    printf("name convert to integer: %d\n", (int)(name));

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);

    return(0);
}

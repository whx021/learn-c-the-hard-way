#include <stdio.h>
#include <ctype.h>
#include <string.h>
// forward declarations
int can_print_it(char ch);
void print_letters(unsigned long length, char arg[]);

void print_arguments(int argc, char *argv[]) {
    int i = 0;
    for (i = 0; i < argc; ++i) {
        print_letters(strlen(argv[i]), argv[i]);
    }
}

void print_letters(unsigned long length, char arg[]) {
    int i = 0;
    for (i = 0; i < length; ++i) {
        char ch = arg[i];
        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
        if (isalnum(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    printf("\n");
}

int can_print_it(char ch) {
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return(0);
}

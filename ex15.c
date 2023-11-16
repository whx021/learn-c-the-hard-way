#include <stdio.h>

void print_info_1(int count, char *names[], int ages[]) {
    int i = 0;
    for (i = 0; i < count; ++i) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }
}

void print_info_2(int count, char **names, int *ages) {
    int i = 0; 
    for (i = 0; i < count; ++i) {
        printf("%s has %d years alive.\n",
                *(names + i), *(ages + i));
    }
}

void print_info_3(int count, char *names[], int *ages) {
    char **cur_name = names;
    int *cur_age = ages;
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; ++cur_name, ++cur_age) {
        printf("%s has %d years alive.\n",
                *cur_name, *cur_age);
    }
}

/* FIXME 
// array convert to pointer in argument
// segmentation fault 
// terminating with default action of signal 8 (SIGFPE)
void print_info_cur(int *count, char **names[], int *ages[]) {
    int i = 0;
    for (i = 0; i < *count; ++i) {
        printf("%s has %d years alive.\n",
                (*names)[i], (*ages)[i]);
    }
}
*/

int main(int argc, char *argv[]) {
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; ++i) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");

    // reverse order method
    for (i = count - 1; i >= 0; --i) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    // cur_age = (int *)names;
    
    // second way using pointers
    for (i = 0; i < count; ++i) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // reverse order method
    for (i = count - 1; i >= 0; --i) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; ++i) {
        printf("%s is %d years old again.\n", 
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // reverse order method
    for (i = count - 1; i >= 0; --i) {
        printf("%s is %d years old again.\n", 
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in stupid complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    printf("---\n");
    
    for (cur_name = &names[count - 1], cur_age = &ages[count - 1];
            cur_age >= ages;
            --cur_name, --cur_age) {
       printf("%s lived %d years so far.\n",
               *cur_name, *cur_age); 
    }

    printf("---\n");

    char **cur_argv = argv;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, cur_argv[i]);
    }    
    
    printf("---\n");
    
    cur_age = ages;
    cur_name = names;
    for (int i = 0; i < count; ++i) {
        printf("name %s address is %p and ages %d address is %p.\n",
                names[i], &names[i], ages[i], &ages[i]);
    }
   
    printf("---\n");
    
    print_info_1(count, names, ages);

    printf("---\n");

    print_info_2(count, names, ages);

    printf("---\n");

    print_info_3(count, names, ages);

    // segmentation fault 
    // terminating with default action of signal 8 (SIGFPE)
    //print_info_cur(&count, &names, &ages);

    return(0);
}

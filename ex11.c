#include <stdio.h>

int main(int argc, char *argv[]) {
    // go througt each string in argv
    
    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        ++i;
    }
    
    i = argc - 1;
    while (i >= 0) {
        printf("arg %d: %s\n", i, argv[i]);
        --i;
    }
        
    // let's make our own array of strings
    char *status[] = {
        "California", "Qregon",
        "Washington", "Texas"
    };

    int num_states = 4;
    i = 0;
    while (i < num_states) {
        printf("state %d: %s\n", i, status[i]);
        ++i;
        if (i == 1) {break;}   
    }
    
    i = num_states - 1;
    while (i >= 0) {
        printf("state %d: %s\n", i, status[i]);
        --i;
    }
    
    i = 0;
    while (i < argc) {
        if (i >= num_states) break;
        status[i] = argv[i];
        ++i;
    }
    
    i = 0;
    while (i < argc) {
        if (i >= num_states) break;
        printf("state %d: %s\n", i, status[i]);
        ++i;
    }

    i = 0;
    while (i < argc) {
        printf("argv[%d] address is %p\n", i, argv[i]);
        ++i;
    }

    i = 0;
    while (i < num_states) {
        printf("status[%d] address is %p\n", i, status[i]);
        ++i;
    }

    return(0);
}

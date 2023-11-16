#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 0;

    // go through each string in argv
    // why am I skipping argv[0]
    for (i = 0; i < argc; ++i) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    
    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas", NULL
    };
/*    
    argv[0] = states[0];
    argv[1] = states[1];
    argv[2] = states[2];
    argv[3] = states[3];
*/

    states[0] = argv[0];
    states[1] = argv[1];
    states[2] = argv[2];
    states[3] = argv[3];

    for (i = 0; i < argc; ++i) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    int num_states = 5;

    for (i = 0; i < num_states; ++i) {
        printf("state %d: %s\n", i, states[i]);
        if (i == 1) {break;}
    }

    return(0);
}

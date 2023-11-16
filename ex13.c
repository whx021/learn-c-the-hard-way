#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you about a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; ++i) {
        char letter = argv[1][i];
        //int test;
        switch (letter) {
            case 'a':
            case 'A':
                printf ("%d: 'A'\n", i);
                break;
            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;
            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;
            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;
            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;
            case 'y':
            case 'Y':
                if (i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                    break;  // no impact on the code
                }
                break;
            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }
    }
 
    i = 0;
    for (i = 0; argv[1][i] != '\0'; ++i) {
        char letter = argv[1][i];
        if (letter >= 'A' && letter <= 'Z') {
            letter += 0x20;
        }
        switch (letter) {
            case 'a':
                printf("%d: 'a'\n", i);
                break;
            case 'e':
                printf("%d: 'e'\n", i);
                break;
            case 'i':
                printf("%d: 'i'\n", i);
                break;
            case 'o':
                printf("%d: 'o'\n", i);
                break;
            case 'u':
                printf("%d: 'u'\n", i);
                break;
            case 'y':
                if (i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'y'\n", i);
                }
                break;
            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }
    }

       
    // iterate over each parameter
    printf("Iterate over each parameter.\n");
    int j = 0;
    for (j = 0; j < argc; ++j) {
        i = 0;
        for (i = 0; argv[j][i] != '\0'; ++i) {
            char letter = argv[j][i];

            switch (letter) {
                case 'a':
                case 'A':
                    printf ("%d: 'A'\n", i);
                    break;
                case 'e':
                case 'E':
                    printf("%d: 'E'\n", i);
                    break;
                case 'i':
                case 'I':
                    printf("%d: 'I'\n", i);
                    break;
                case 'o':
                case 'O':
                    printf("%d: 'O'\n", i);
                    break;
                case 'u':
                case 'U':
                    printf("%d: 'U'\n", i);
                    break;
                case 'y':
                case 'Y':
                    if (i > 2) {
                        // it's only sometimes Y
                        printf("%d: 'Y'\n", i);
                    }
                    break;
                default:
                    printf("%d: %c is not a vowel\n", i, letter);
            }
        }
    }  
    
    for (i = 0; argv[1][i] != '\0'; ++i) {
        char letter = argv[1][i];

        if (letter == 'a' || letter == 'A') {
            printf("%d: 'A'\n", i);
        } else if (letter == 'e' || letter == 'E') {
            printf("%d: 'E'\n", i);
        } else if (letter == 'i' || letter == 'I') {
            printf("%d: 'I'\n", i);
        } else if (letter == 'o' || letter == 'O') {
            printf("%d: 'O'\n", i);
        } else if (letter == 'u' || letter == 'U') {
            printf("%d: 'U'\n", i);
        } else if (letter == 'y' || letter == 'Y') {
            if (i > 2) {
                // it's only sometimes Y
                printf("%d: 'Y'\n", i);
            }
        } else {
            printf("%d: %c is not a vowel\n", i, letter);
        }
    }

    return(0);
}

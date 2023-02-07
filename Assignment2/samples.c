
// Compile using
// $ gcc samples.c -o sample

// Run using
// $ ./sample 1
// for sample case 1 or
// $ ./sample 2
// for sample case 2 or
// $ ./sample 3
// for an extra case

// This program can be used directly with the interative runner python file

#include <stdio.h>
#include <stdlib.h>

// Simulate the satalite taking photos given
// * some max speed
// * some max position
// * the actual speed
// * the actual starting position
void type1(int S, int L, int sp, int loc) {

    // Print the starting bounds
    printf("%d %d\n", S, L);
    fflush(stdout);
    
    // Track the location
    int curLoc = loc;
    
    // Give the student only 24 hours >:)
    for (int i = 0; i < 24; i++) {
        int guess;
    
        // Move the boat forward
        curLoc += sp;
        char c;
        
        // Read until end of stream is reached
        while (c = getc(stdin)) {
        
            // Check if sending rescue team
            if (c == '!') {
                // Read guess
                scanf("%d", &guess);
                
                // Check guess
                if (guess == curLoc) {
                    fprintf(stderr, "CORRECT!\n");
                    return;
                } else {
                    fprintf(stderr, 
                        "WRONG ANSWER\nRescue team did not find the boat.\n");
                    fprintf(stderr, "Expected: %d\nRecieved: %d\n",
                            curLoc, guess);
                    return;
                }
            } else if (c == '?') {
                // Read location for photo
                scanf("%d", &guess);
                
                // Determine accuracy
                if (guess == curLoc) {
                    printf("Boat!\n");
                    fflush(stdout);
                } else if (guess < curLoc) {
                    printf("Wake\n");
                    fflush(stdout);
                } else {
                    printf("No Wake\n");
                    fflush(stdout);
                }
                break;
            } else if (c == '\n') {

            } else {
                fprintf(stderr, "INVALID QUERY TYPE\n");
                fflush(stderr);
            }
        }
        if (!c) {
            break;
        }
    }
    fprintf(stderr, "WRONG ANSWER\nDid not make a guess in time.\n");
}

// The main function
int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Please provide a case number (1, 2, or 3) as an arguement\n");
        return 0;
    }

    // Determine the test case 
    int test_case = atoi(argv[1]);

    // Check which test case is used
    switch (test_case) {
        case 1:
            type1(3, 3, 2, 0); // Sample 1
            break;
        case 2:
            type1(5, 2, 5, 2); // Sample 2
            break;
        case 3:
            type1(50, 60, 32, 53); // Extra test Case
            break;
        default:
            fprintf(stderr, "ERROR: Invalid case # (%d)\n", test_case);
    };

    return 0;
}

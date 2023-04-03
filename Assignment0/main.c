#include <stdio.h>
#include <string.h>
#define MAX_SHIP_NAME_LENGTH 20
#define MAX_SHIPS_PER_LINE 100
#define MAX_SHIP_LINES 100
// The following value is how many characters could be in a single line
// number of non-whitespace characters, number of spaces,
// number of new lines, number of NULL terminators
#define BUFFER_LEN (MAX_SHIPS_PER_LINE) * (MAX_SHIP_NAME_LENGTH) + (MAX_SHIPS_PER_LINE - 1) + 1 + 1
int main() {
    int ship_lines, customers;
    char garbage[5];
    //Loads in number of ship lines
    scanf("%d", &ship_lines);
    fgets(garbage, 5, stdin);
    char names[MAX_SHIP_LINES][MAX_SHIPS_PER_LINE][MAX_SHIP_NAME_LENGTH + 1];
    int ships_per_line[ship_lines];
    int current_line_in = 0;
    //Loop load in number of lines asked for
    while (current_line_in < ship_lines){
        char line[BUFFER_LEN];
        fgets(line, BUFFER_LEN, stdin);
        int line_len = strlen(line);
        int ship_counter = 0;
        int ship_idx = 0;
        //Iterate chars in line, stores each ship name in diff arrays
        for (int current_char = 0; current_char < line_len; current_char++){
            //Move onto next ship, next array same line, up ship count
            if (line[current_char] == ' ') {
                names[current_line_in][ship_counter][ship_idx] = '\0';
                ship_counter++;
                ship_idx = 0;
            }
            //End of this line, sets final ships of line count, by adding one.
            else if (line[current_char] == '\n'){
                ships_per_line[current_line_in] = ++ship_counter;
                ship_idx = 0;
                break;
            }
            //Add current character to current array for current ship
            else {
                names[current_line_in][ship_counter][ship_idx] = line[current_char];
                ship_idx++;
            }
        }
        current_line_in++;
    }
    //Scan for amount of customers/requests
    scanf("%d", &customers);
    fgets(garbage, 5, stdin);
    //Loop for length of amount of customers
    // asks for week wanted for each loop and prints the ships ava for the week
    for (int current_cust=0; current_cust < customers; current_cust++){
        int wanted_week;
        scanf("%d", &wanted_week);
        fgets(garbage, 5, stdin);
        for (int current_line=0; current_line < ship_lines; current_line++){
            int ship_ava_for_line;
            ship_ava_for_line = (wanted_week%ships_per_line[current_line]);
            if (ship_ava_for_line != 0){
                ship_ava_for_line--;
            }
            else {
                ship_ava_for_line = ships_per_line[current_line]-1;
            }
            printf("%s ", names[current_line][ship_ava_for_line]);
        }
        printf("\n");
    }
    return 0;
}

//
// Created by hatoa on 8/1/2025.
//
#include <stdio.h>

#include "tripletquizzer.h"
int main(){
    while(1) {
        printf(
      "\nWelcome to the boggle practice CLI!\n"
      "Press 1 to access the triplet quizzer\n"
      "Press 2 to access the boggle puzzles\n"
      "Press anything else to exit\n"
    );

        // Get input from the user
        char input[2];
        printf("Your choice: ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Use switch case to handle input
            switch (input[0]) { // Check the first character of input
                case '1':
                    tripletquizzer();
                break;
                case '2':
                    while (getchar() != '\n'){}
                    printf("Not implemented!");
                break;
                default:
                    printf("Exiting the program. Goodbye!\n");
                return 0;
            }
        } else {
            printf("Error reading input. Exiting.\n");
            return 1;
        }
    }
}
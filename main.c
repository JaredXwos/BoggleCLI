//
// Created by hatoa on 8/1/2025.
//
#include <stdio.h>
#include "speedpuzzler.h"
#include "tripletquizzer.h"
int main(){
    while(1) {
        printf(
      "\nWelcome to the boggle practice CLI!\n"
      "Press 1 to access the triplet quizzer\n"
      "Press 2 to access the 'ester' boggle puzzles\n"
      "Press 3 to access the 'rates' boggle puzzles\n"
      "Press 4 to access the 'least' boggle puzzles\n"
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
                    speedPuzzler("ester");
                    while (getchar() != '\n'){}
                break;
                case '3':
                    speedPuzzler("rates");
                    while (getchar() != '\n'){}
                break;
                case '4':
                    speedPuzzler("least");
                while (getchar() != '\n'){}
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
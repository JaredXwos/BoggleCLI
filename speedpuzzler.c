//
// Created by hatoa on 8/1/2025.
//
#include <stdio.h>
#include <time.h>
#include "speedpuzzler.h"
#ifdef _WIN32
#include <windows.h>
static void enableANSI() {
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

// Function to print the king string in batches of 4 characters
void print_king(const char king[17]) {
    for (int i = 0; i < 16; i += 4) {
        printf("%.4s\n", &king[i]); // Print 4 characters at a time
    }
}

// Function to check if a word exists in the list of answers
int is_correct_answer(const char *word, char **answers) {
    for (int i = 0; answers[i] != NULL; i++) {
        if (strcmp(word, answers[i]) == 0) {
            return 1; // Word found in answers
        }
    }
    return 0; // Word not found
}

// Function to count the total number of correct answers in the board
int count_total_answers(char **answers) {
    int count = 0;
    while (answers[count] != NULL) {
        count++;
    }
    return count;
}

int speedpuzzler() {
#ifdef _WIN32
    enableANSI(); // Enable ANSI support on Windows
#endif

    // Seed the random number generator
    srand(time(NULL));
    printf("This quiz provides a limited preset board. Type all valid words findable on the board.\n"
           "Press enter after every word.\n"
           "Type space and press enter to exit\n");

     int question_count = 0;

    while (1) {
        // Increment the question count and pick a random board
        question_count++;
        int random_index = rand() % total_boards;
        const struct board *current_board = &list[random_index];

        printf("\n--- Question %d ---\n", question_count);

        // Print the king string
        print_king(current_board->king);


        // Get user input
        printf("\nType your answers (type a blank space to finish, or 'QUIT' to exit):\n");
        char input[100];
        char *user_answers[100] = {0}; // Array to store user-entered words
        int user_count = 0;

        while (1) {
            printf("> ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline

            if (strcmp(input, "QUIT") == 0) {
                printf("Exiting the quiz. Thanks for playing!\n");
                // Free any dynamically allocated memory before exiting
                for (int i = 0; i < user_count; i++) {
                    free(user_answers[i]);
                }
                return 0;
            }

            if (strcmp(input, "") == 0) { // Blank space to finish
                break;
            }

            // Store the user input
            user_answers[user_count] = strdup(input);
            user_count++;
        }

        // Verify user answers
        int score = 0;
        const int total_answers = count_total_answers(current_board->answer);
        const char *missed[100] = {0}; // Array to store missed answers
        char *wrong[100] = {0};  // Array to store incorrect answers
        int missed_count = 0, wrong_count = 0;

        // Check user answers
        for (int i = 0; i < user_count; i++) {
            if (is_correct_answer(user_answers[i], current_board->answer)) {
                score++;
            } else {
                wrong[wrong_count++] = user_answers[i];
            }
        }

        // Find missed answers
        for (int i = 0; current_board->answer[i] != NULL; i++) {
            int found = 0;
            for (int j = 0; j < user_count; j++) {
                if (strcmp(current_board->answer[i], user_answers[j]) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                missed[missed_count++] = current_board->answer[i];
            }
        }

        // Display results
        printf("\n--- Results ---\n");
        printf("Correct: %d / %d\n", score, total_answers);

        if (missed_count > 0) {
            printf("Missed:\n");
            for (int i = 0; i < missed_count; i++) {
                printf("- %s\n", missed[i]);
            }
        }

        if (wrong_count > 0) {
            printf("Wrong:\n");
            for (int i = 0; i < wrong_count; i++) {
                printf("- %s\n", wrong[i]);
                free(wrong[i]); // Free dynamically allocated wrong answers
            }
        }

        // Free user-entered answers
        for (int i = 0; i < user_count; i++) {
            free(user_answers[i]);
        }
    }
}

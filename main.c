#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TOTAL_COMBINATIONS 17576  // 26^3
#define FILENAME "threedirections.txt"

// Function to convert a three-letter combination to an index
int combination_to_index(const char *combination) {
    if (strlen(combination) != 3) return -1;

    int index = 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(combination[i])) return -1; // Ensure only letters
        index = index * 26 + (toupper(combination[i]) - 'A');
    }
    return index;
}

// Function to convert an index back to a three-letter combination
void index_to_combination(int index, char *combination) {
    for (int i = 2; i >= 0; i--) {
        combination[i] = 'A' + (index % 26);
        index /= 26;
    }
    combination[3] = '\0';
}

// Function to initialize index groups based on value (w, a, s, d)
void group_indices_by_value(const char *values, int **groups, int *group_sizes) {
    // Initialize sizes to 0
    for (int i = 0; i < 4; i++) {
        group_sizes[i] = 0;
    }

    // First pass: Count how many indices belong to each group
    for (int i = 0; i < TOTAL_COMBINATIONS; i++) {
        switch (values[i]) {
            case 'W': group_sizes[0]++; break;
            case 'A': group_sizes[1]++; break;
            case 'S': group_sizes[2]++; break;
            case 'D': group_sizes[3]++; break;
            default: printf("Invalid combination %d.\n", values[i]); break;;
        }
    }

    // Allocate memory for each group
    for (int i = 0; i < 4; i++) {
        groups[i] = malloc(group_sizes[i] * sizeof(int));
        if (groups[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for group %d.\n", i);
            exit(1);
        }
    }

    // Second pass: Populate the groups with indices
    int group_counters[4] = {0};
    for (int i = 0; i < TOTAL_COMBINATIONS; i++) {
        switch (values[i]) {
            case 'W': groups[0][group_counters[0]++] = i; break;
            case 'A': groups[1][group_counters[1]++] = i; break;
            case 'S': groups[2][group_counters[2]++] = i; break;
            case 'D': groups[3][group_counters[3]++] = i; break;
            default: printf("Invalid combination %d.\n", values[i]); break;
        }
    }
}

// Main function
int main() {
    char *values = malloc(TOTAL_COMBINATIONS);
    if (values == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    // Load values from the text file
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", FILENAME);
        free(values);
        return 1;
    }

    // Read the space-separated values into the array
    for (int i = 0; i < TOTAL_COMBINATIONS; i++) {
        if (fscanf(file, " %c", &values[i]) != 1) {
            fprintf(stderr, "File does not contain the expected data.\n");
            fclose(file);
            free(values);
            return 1;
        }
        if (strchr("WASD", values[i]) == NULL) {
            fprintf(stderr, "Invalid character in file: %c\n", values[i]);
            fclose(file);
            free(values);
            return 1;
        }
    }
    fclose(file);

    // Group indices by their values (w, a, s, d)
    int *groups[4];         // Array of pointers to store indices for each group
    int group_sizes[4];     // Sizes of each group
    group_indices_by_value(values, groups, group_sizes);

    // Seed the random number generator
    srand(time(NULL));

    // Start the quiz
    printf("This quiz tests you on how fast you can see 3 letter words.)\n"
           "If reading the letters left to right forms a word, e.g. ALT, press A\n"
           "If reading the letters right to left forms a word, e.g. UYR, press D\n"
           "If reading the letters in either direction both form words, e.g. LET, press W\n"
           "If there are no words, press S\n"
           "Press space to exist and see your averages");
    int question = 0, score = 0;
    // Start tracking time
    time_t start_time, end_time;
    time(&start_time);
    while (1) {
        char input;
        // Randomly select a target value group (0 = 'w', 1 = 'a', 2 = 's', 3 = 'd')
        const int target_group = rand() % 4;

        // Randomly select an index within the chosen group
        const int random_index = groups[target_group][rand() % group_sizes[target_group]];

        // Convert the index to a three-letter combination
        char combination[4];
        index_to_combination(random_index, combination);

        // Ask the user
        printf("\n%d: Is '%s' a word? ", ++question, combination);
        scanf("%c", &input);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF){}
        if(input==' '){
            printf("Exiting...\n");
            break;
        }
        if(strchr("WASD", input) == NULL) printf("\b");

        if(values[random_index]==input) {
            printf("Correct");
            ++score;
        }
        else printf("Incorrect. The correct value is %c.\n", values[random_index]);
        printf(" Score: %d", score);
    }
    // End tracking time
    time(&end_time);
    double elapsed_time = difftime(end_time, start_time);
    printf("Elapsed time: %f seconds\n"
           "Accuracy: %d%%\n ", elapsed_time, 100*score/question);

    // Clean up
    free(values);
    return 0;
}
//
// Created by hatoa on 4/1/2025.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char inputfile[] = "leastpolykings.txt";
char outputfile[] = "resolvedleastpolykings.txt";
static const char *const validester[] = {
    "ERE", "ERES", "ERS", "ERST", "EST", "ESTER",
    "REE", "REES", "REEST", "RES", "RESET", "REST", "RET", "RETE", "RETS",
    "SEE", "SEER", "SER", "SERE", "SET", "STEER", "STERE",
    "TEE", "TEER", "TEERS", "TEES", "TERES", "TERSE", "TES", "TREE", "TREES", "TRES"
};

static const char *const validrates[] = {
    "ARE", "ARES", "ARET", "ARETS", "ARS", "ARSE", "ART", "ARTS", "ASTER", "ATE", "ATES", "ATS",
    "EAR", "EARS", "EARST", "EAS", "EAST", "EAT", "EATS", "ERA", "ERAS", "ERS", "ERST", "EST", "ETA", "ETAS",
    "RAS", "RASE", "RAST", "RAT", "RATE", "RATES", "RATS", "REAST", "RES", "RESAT", "REST", "RET", "RETS",
    "SAE", "SAR", "SAT", "SATE", "SEA", "SEAR", "SEAT", "SER", "SERA", "SET", "SETA", "STAR", "STARE", "STRAE",
    "TAE", "TAES", "TAR", "TARE", "TARES", "TARS", "TAS", "TASE", "TASER", "TEA", "TEAR", "TEARS", "TEAS", "TERAS",
    "TES", "TRES", "TSAR"
};

static const char *const validleast[] = {
    "TES", "SET", "EST", "TEL", "LET", "ELT", "SEL", "ELS", "TAS", "SAT", "ATS", "LAT", "ALT", "SAL" "LAS", "TEA",
    "TAE", "ETA", "EAT", "ATE", "SEA", "SAE", "EAS", "LEA", "ALE", "TELS", "LETS", "ELTS", "LEST", "SLAT", "SALT",
    "LATS", "LAST", "ALTS", "TEAS", "TASE", "TAES", "SETA", "SEAT", "SATE", "ETAS", "EATS", "EAST", "ATES", "TELA"
    "TEAL", "TALE", "TAEL", "LEAT", "LATE", "SLAE", "SEAL", "SALE", "LEAS", "LASE", "ALES", "TESLA", "TEALS", "TALES",
    "TAELS", "STELA", "STEAL", "STALE", "SLATE", "SETAL", "SALET", "LEATS", "LEAST"
};

struct node {
    struct node* tl;     // Top-left
    struct node* tr;     // Top-right
    struct node* bl;     // Bottom-left
    struct node* br;     // Bottom-right
    struct node* top;    // Top
    struct node* bottom; // Bottom
    struct node* left;   // Left
    struct node* right;  // Right
    char letter;
    int index;
} grid[16];


void initialize_grid() {
    for (int i = 0; i < 16; i++) {
        const int cols = 4;
        const int rows = 4;
        // Calculate row and column of current node
        const int row = i / cols;
        const int col = i % cols;

        // Link neighbors
        grid[i].tl = (row > 0 && col > 0) ? &grid[(row - 1) * cols + (col - 1)] : 0;
        grid[i].tr = (row > 0 && col < cols - 1) ? &grid[(row - 1) * cols + (col + 1)] : 0;
        grid[i].bl = (row < rows - 1 && col > 0) ? &grid[(row + 1) * cols + (col - 1)] : 0;
        grid[i].br = (row < rows - 1 && col < cols - 1) ? &grid[(row + 1) * cols + (col + 1)] : 0;

        grid[i].top = (row > 0) ? &grid[(row - 1) * cols + col] : 0;
        grid[i].bottom = (row < rows - 1) ? &grid[(row + 1) * cols + col] : 0;
        grid[i].left = (col > 0) ? &grid[row * cols + (col - 1)] : 0;
        grid[i].right = (col < cols - 1) ? &grid[row * cols + (col + 1)] : 0;

        // Initialize other fields
        grid[i].index = i; // Set the index
    }
}

void fill_grid(const char* polyking){
  for(int i = 0; i < 16; i++) grid[i].letter = polyking[i];
}

struct unfilteredstring{
  char* string;
  struct unfilteredstring* next;
};

struct unfilteredstring *head = 0, *tail;

void insertIfNew(char* word) {
    // Handle the case where the list is initially empty
    if (!head) {
        head = (struct unfilteredstring*)malloc(sizeof(struct unfilteredstring));
        head->string = (char*) malloc(6);
        strcpy(head->string, word);
        head->next = NULL;
        return;
    }

    if (!strcmp(word, head->string)) return;

    struct unfilteredstring *listtail = head;
    // Traverse the list and check if the word already exists
    for (; listtail->next != NULL; listtail = listtail->next) {
        if (!strcmp(word, listtail->next->string)) return; // Word already exists
    }

    // Append a new node to the end of the list
    listtail->next = (struct unfilteredstring*)malloc(sizeof(struct unfilteredstring));
    listtail = listtail->next; // Move to the new node
    listtail->string = (char*)malloc(strlen(word) + 1);
    strcpy(listtail->string, word);
    listtail->next = NULL; // Initialize the next pointer
}


void modifiedDFS(struct unfilteredstring* listhead, int index, int count, char* word, int* checked){
    // Max depth 5
    if(count>5) return;
    // Add the letter to the word
    char newword[6] = "";
    strcpy(newword, word);
    strcat(newword, &grid[index].letter);
    // Add the square to checked
    int newchecked[16];
    memcpy(newchecked, checked, sizeof(int)*16);
    newchecked[index] = 1;
    // If long enough, store the word
    if(count > 2) {
      insertIfNew(newword);
    }
    // Assuming grid[index] has pointers for tl, top, tr, left, right, bl, bottom, br
    struct node *directions[] = {grid[index].tl, grid[index].top, grid[index].tr, grid[index].left,
                          grid[index].right, grid[index].bl, grid[index].bottom, grid[index].br};

    for (int i = 0; i < 8; i++) {
        if (directions[i] != NULL && newchecked[directions[i]->index] == 0 && directions[i]->letter != '_') {
            modifiedDFS(listhead, directions[i]->index, count + 1, newword, newchecked);
        }
    }
}

// Function to filter the linked list
void filterhead(const char* minidict) {
    struct unfilteredstring* current = head;
    struct unfilteredstring* prev = NULL;

    while (current) {
        if(!strcmp("ester", minidict)){
            for (int i = 0; i < sizeof(validleast)/sizeof(validleast[0]); i++) {
                if (!strcmp(current->string, validleast[i])) {
                    prev = current;
                    current = current->next;
                    goto End;
                }
            }
            struct unfilteredstring* temp = current;
            if (prev == NULL) {
                // Removing the head node
                head = current->next;
            } else {
                // Removing a node in the middle or end
                prev->next = current->next;
            }
            current = current->next;

            // Free the memory of the removed node
            free(temp->string);
            free(temp);
        }
        End:;
    }
}

void freeHead(){
    struct unfilteredstring* current = head;
    while(current){
        struct unfilteredstring* temp = current;
        current = current->next;
        if(temp->string) free(temp->string);
        free(temp);
    }
    head = 0;
}

void resolvePolyking(const char* polyking) {
    freeHead();
    fill_grid(polyking);
    char word[6] = "";
    int checked[16] = {0};
    for(int i = 0; i < 16; i++) modifiedDFS(head, i, 1, word, checked);
    filterhead("ester");
}

int main(){
    initialize_grid();
    FILE* inputFile = fopen(inputfile, "r");
    if (!inputFile) {
        perror("Failed to open input file");
        return 1;
    }

    FILE* outputFile = fopen(outputfile, "w");
    if (!outputFile) {
        perror("Failed to open output file");
        fclose(inputFile);
        return 1;
    }

    char buffer[17];  // Buffer to read lines from the file
    int counter = 0;
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        // Remove newline character, if present
        buffer[strcspn(buffer, "\n")] = '\0';
        buffer[strcspn(buffer, "\n")] = '\0';
        if (!strlen(buffer)) continue;
        // Call the `solve` function on the input string
        resolvePolyking(buffer);

        // Write the input string to the output file
        //for (int i = 0; i < 16; i += 4) printf("%.4s\n", &buffer[i]); // Print 4 characters at a time

        fprintf(outputFile, "{\"%s\", (const char *[]){", buffer);

        // Write all strings from the global list to the output file
        struct unfilteredstring *current = head;
        while (current) {
            fprintf(outputFile, "\"%s\",", current->string);
            if(!(++counter % 1000)) printf(".");
            current = current->next;
        }
        fprintf(outputFile, "NULL}},");
        //printf("");
    }
    printf("\n%d ", counter);
    freeHead();
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Output written to %s.\n",outputfile);
}
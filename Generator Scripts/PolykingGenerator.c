//
// Created by hatoa on 3/1/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node* tl;     // Top-left
    struct node* tr;     // Top-right
    struct node* bl;     // Bottom-left
    struct node* br;     // Bottom-right
    struct node* top;    // Top
    struct node* bottom; // Bottom
    struct node* left;   // Left
    struct node* right;  // Right
    int ismarked;
    int index;
} grid[16];

struct polyking {
    int* coordinates;
    struct polyking* next;
};
struct polyking head;
struct polyking *tail;

void initialize_grid() {
    for (int i = 0; i < 16; i++) {
        const int cols = 4;
        const int rows = 4;
        // Calculate row and column of current node
        const int row = i / cols;
        const int col = i % cols;

        // Link neighbors
        grid[i].tl = (row > 0 && col > 0) ? &grid[(row - 1) * cols + (col - 1)] : NULL;
        grid[i].tr = (row > 0 && col < cols - 1) ? &grid[(row - 1) * cols + (col + 1)] : NULL;
        grid[i].bl = (row < rows - 1 && col > 0) ? &grid[(row + 1) * cols + (col - 1)] : NULL;
        grid[i].br = (row < rows - 1 && col < cols - 1) ? &grid[(row + 1) * cols + (col + 1)] : NULL;

        grid[i].top = (row > 0) ? &grid[(row - 1) * cols + col] : NULL;
        grid[i].bottom = (row < rows - 1) ? &grid[(row + 1) * cols + col] : NULL;
        grid[i].left = (col > 0) ? &grid[row * cols + (col - 1)] : NULL;
        grid[i].right = (col < cols - 1) ? &grid[row * cols + (col + 1)] : NULL;

        // Initialize other fields
        grid[i].ismarked = 0;
        grid[i].index = i; // Set the index
    }
}

void print_cell(const int index) {
    if(grid[index].tl != NULL) printf("%d ", grid[index].tl->index);
    if(grid[index].top != NULL) printf("%d ", grid[index].top->index);
    if(grid[index].tr != NULL) printf("%d", grid[index].tr->index);
    printf("\n");
    if(grid[index].left != NULL) printf("%d ", grid[index].left->index);
    printf("%d ",index);
    if(grid[index].right != NULL) printf("%d", grid[index].right->index);
    printf("\n");
    if(grid[index].bl != NULL) printf("%d ", grid[index].bl->index);
    if(grid[index].bottom != NULL) printf("%d ", grid[index].bottom->index);
    if(grid[index].br != NULL) printf("%d", grid[index].br->index);
    printf("\n\n");
}

void recursiveAppendKing(const int dir, const int count, const int index, const int* opath) {
    int path[count];
    memcpy(path, opath, count * sizeof(int));
    path[count-1] = index;
    for(int i = 0; i < count; i++) printf("%d ", path[i]);
    if(count == 5) {
        tail->next = malloc(sizeof(struct polyking));
        tail = tail->next;
        tail->coordinates = malloc(sizeof(int) * 5);
        memcpy(tail->coordinates, path, 5 * sizeof(int));
        return;
    }
    path[count] = index;
    if(grid[index].tl != NULL && dir != 9) recursiveAppendKing(1, count+1, grid[index].tl->index, path);
    if(grid[index].top != NULL && dir != 8) recursiveAppendKing(2, count+1, grid[index].top->index, path);
    if(grid[index].tr != NULL && dir != 7) recursiveAppendKing(3, count+1, grid[index].tr->index, path);
    if(grid[index].left != NULL && dir != 6) recursiveAppendKing(4, count+1, grid[index].left->index, path);
    if(grid[index].right != NULL && dir != 4) recursiveAppendKing(6, count+1, grid[index].right->index, path);
    if(grid[index].bl != NULL && dir != 3) recursiveAppendKing(7, count+1, grid[index].bl->index, path);
    if(grid[index].bottom != NULL && dir != 2) recursiveAppendKing(8, count+1, grid[index].bottom->index, path);
    if(grid[index].br != NULL && dir!= 1) recursiveAppendKing(9, count+1, grid[index].br->index, path);
}

char* polykingToString(const int* polyking) {
    char *returnstring = malloc(sizeof(char) * 170);
    returnstring[0] = '\0';
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 5; j++) {
            if(polyking[j] == i) {
                strcat(returnstring, "M");
                goto End;
            }
        }
        strcat(returnstring, "0");
        End:
    }
    return returnstring;
}

int main() {
    initialize_grid();
    tail = &head;
    for (int i = 0; i < 16; i++) {
        int path[5];
        recursiveAppendKing(-1, 1, i, path);
    }
    // Open the file in write mode
    FILE* file = fopen("unfilteredpolykings.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1; // Exit with error if the file cannot be opened
    }

    int count = 0;
    for(const struct polyking *i = &head;i!=NULL;i=i->next) {
        ++count;
        if(i->coordinates) {
            printf("%s\n", polykingToString(i->coordinates));
            fprintf(file, "%s\n", polykingToString(i->coordinates));
        }
        else printf("VOID\n");
    }

    // Close the file
    fclose(file);

    printf("Count: %d\n", count);

    return 0;
}
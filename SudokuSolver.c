#include <stdio.h>
#include <time.h>

const short shortshift[10] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};
int numCalls = 0;

typedef struct {
    unsigned char grid[9][9];
    unsigned short row[9];
    unsigned short col[9];
    unsigned short box[9];
    unsigned char pos;
} Sudoku;

Sudoku initSudoku(char puzzle[9][9]) {
    Sudoku mySudoku = {.row = {0}, .col = {0}, .box = {0}};
    char r, c;
    char val;
    short one;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            val = puzzle[r][c];
            one = shortshift[val];
            mySudoku.grid[r][c] = val;
            mySudoku.row[r] |= one;
            mySudoku.col[c] |= one;
            mySudoku.box[(c/3) + 3*(r/3)] |= one;
        }
    }
    mySudoku.pos = 0;
    return mySudoku;
}

void printSudoku(Sudoku myPuzzle) {
    char r,c;
    printf("The solution is \n\n");
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf("%d  ", myPuzzle.grid[r][c]);
        }
        printf("\n\n");
    }
    printf("\n");
}

int main(void) {
    int i=0,j=0;
    //char myPuz[9][9] ={{8,5,0,0,0,2,4,0,0}, {7,2,0,0,0,0,0,0,9},{0,0,4,0,0,0,0,0,0},{0,0,0,1,0,7,0,0,2},{3,0,5,0,0,0,9,0,0},{0,4,0,0,0,0,0,0,0},{0,0,0,0,8,0,0,7,0},{0,1,7,0,0,0,0,0,0},{0,0,0,0,3,6,0,4,0}} ;

    // This is a completely empty grid, so the program can theoretically generate all possible sudoku solutions ever. Used to compare runtimes between different solving algos.
    char myPuz[9][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    // Super easy sudoku
    // char myPuz[9][9] = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};

    // This sudoku has multiple solutions
    //char myPuz[9][9] = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

    printf("\n\nSudoku Puzzle is \n\n");
    for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                printf("%d  ",myPuz[i][j]);
            }
         printf("\n\n");
        }
    clock_t begin, end;
    double time_spent;
    begin = clock();
    Sudoku myPuzzle = initSudoku(myPuz);
    solve(myPuzzle);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nElapsed: %g seconds\n", time_spent);
    return 0;

}

void solve(Sudoku puzzle) {
    short one, valids;
    char r, c, val;
    // To prevent an infinite loop
    if (numCalls == 10000) {
        return;
    }
    numCalls++;
    r = puzzle.pos >> 4;
    c = puzzle.pos & 15;
// The loop that iterates traverses the grid
    while (r < 9) {
        while (c < 9) {
            if (!puzzle.grid[r][c]) {
                valids = ~(puzzle.row[r] | puzzle.col[c] | puzzle.box[(c/3) + 3*(r/3)]);
                for (val = 1; val <= 9; val++) { // Iterates through the valid entries for that cell in ascending order.
                    one = shortshift[val];
                    if (one & valids) {
                        Sudoku newPuzzle;
                        newPuzzle = puzzle;
                        newPuzzle.grid[r][c] = val;
                        newPuzzle.row[r] |= one;
                        newPuzzle.col[c] |= one;
                        newPuzzle.box[(c/3) + 3*(r/3)] |= one;
                        newPuzzle.pos = r << 4 | c;
                        solve(newPuzzle);
                    }
                }
                return;
            }
            c++;
        }
        c = 0;
        r++;
    }
    printSudoku(puzzle);

}

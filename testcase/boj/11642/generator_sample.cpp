#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static void shiftRow(vector<string>& grid, int row, int amount) {
    amount = (amount % 4 + 4) % 4;
    string shifted = grid[row];
    for (int col = 0; col < 4; ++col) {
        shifted[(col + amount) % 4] = grid[row][col];
    }
    grid[row] = shifted;
}

static void shiftColumn(vector<string>& grid, int col, int amount) {
    amount = (amount % 4 + 4) % 4;
    vector<char> shifted(4);
    for (int row = 0; row < 4; ++row) {
        shifted[(row + amount) % 4] = grid[row][col];
    }
    for (int row = 0; row < 4; ++row) {
        grid[row][col] = shifted[row];
    }
}

static vector<string> solvedGrid() {
    return {"RRRR", "GGGG", "BBBB", "YYYY"};
}

static vector<string> randomPermutationGrid() {
    string cells = "RRRRGGGGBBBBYYYY";
    shuffle(cells.begin(), cells.end());

    vector<string> grid(4, string(4, 'R'));
    int index = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            grid[row][col] = cells[index++];
        }
    }
    return grid;
}

static vector<string> shiftedGrid() {
    vector<string> grid = solvedGrid();
    int moves = rnd.next(1, 12);
    for (int i = 0; i < moves; ++i) {
        int line = rnd.next(0, 3);
        int amount = rnd.next(1, 3);
        if (rnd.next(0, 1) == 0) {
            shiftRow(grid, line, amount);
        } else {
            shiftColumn(grid, line, amount);
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> grid;
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        grid = solvedGrid();
    } else if (mode == 1) {
        grid = shiftedGrid();
    } else {
        grid = randomPermutationGrid();
    }

    for (const string& row : grid) {
        println(row);
    }
    return 0;
}

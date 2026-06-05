#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string directions = "LRUD";
    const vector<int> mirrorable = {1, 2, 5, 8};
    const vector<int> ambiguous = {3, 4, 6, 7, 9};
    const vector<int> allDigits = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    char w = directions[rnd.next(0, 3)];
    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode == 1) {
        n = rnd.next(17, 20);
    } else {
        n = rnd.next(2, 12);
    }

    vector<vector<int>> grid(n, vector<int>(n));
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (mode == 0) {
                grid[row][col] = rnd.any(mirrorable);
            } else if (mode == 1) {
                grid[row][col] = rnd.any(allDigits);
            } else if (mode == 2) {
                grid[row][col] = rnd.any(ambiguous);
            } else if (mode == 3) {
                grid[row][col] = ((row + col) % 2 == 0) ? rnd.any(mirrorable) : rnd.any(ambiguous);
            } else if (mode == 4) {
                grid[row][col] = (row % 2 == 0) ? rnd.any(mirrorable) : rnd.any(ambiguous);
            } else {
                grid[row][col] = (col % 2 == 0) ? rnd.any(ambiguous) : rnd.any(mirrorable);
            }
        }
    }

    println(w, n);
    for (const auto& row : grid) {
        println(row);
    }

    return 0;
}

#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read R and C
    int R = inf.readInt(2, 20, "R");
    inf.readSpace();
    int C = inf.readInt(2, 20, "C");
    inf.readEoln();

    // 2. Read the puzzle grid
    vector<string> grid(R);
    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readLine("[a-z#]{" + vtos(C) + "}", "row");
        ensuref((int)grid[i].size() == C, "Row %d does not have exactly %d characters", i+1, C);
    }

    // 3. Validate that there is at least one word (guaranteed by statement, but let's check)
    // A word is a maximal horizontal or vertical sequence of >=2 consecutive lowercase letters, not interrupted by '#'
    // Let's extract all words and ensure at least one exists

    set<string> words;

    // Horizontal words
    for (int i = 0; i < R; ++i) {
        int j = 0;
        while (j < C) {
            // Find start of a word
            if (islower(grid[i][j])) {
                int start = j;
                while (j < C && islower(grid[i][j])) ++j;
                int len = j - start;
                if (len >= 2) {
                    string w = grid[i].substr(start, len);
                    words.insert(w);
                }
            } else {
                ++j;
            }
        }
    }

    // Vertical words
    for (int col = 0; col < C; ++col) {
        int i = 0;
        while (i < R) {
            if (islower(grid[i][col])) {
                int start = i;
                while (i < R && islower(grid[i][col])) ++i;
                int len = i - start;
                if (len >= 2) {
                    string w;
                    for (int k = start; k < i; ++k) w += grid[k][col];
                    words.insert(w);
                }
            } else {
                ++i;
            }
        }
    }

    ensuref(!words.empty(), "There must be at least one word in the puzzle");

    inf.readEof();
}

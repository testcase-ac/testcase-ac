#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Tree {
    int x, y;
    bool infected;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<Tree> trees;
    trees.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-250, 250, "x");
        inf.readSpace();
        int y = inf.readInt(-250, 250, "y");
        inf.readSpace();
        char p = inf.readChar();
        inf.readEoln();

        ensuref(p == 'I' || p == 'N',
                "p must be 'I' or 'N', got '%c' at tree %d", p, i + 1);

        trees.push_back({x, y, p == 'I'});
    }

    // Check distinct locations
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(!(trees[i].x == trees[j].x && trees[i].y == trees[j].y),
                    "Trees %d and %d have the same location (%d, %d)",
                    i + 1, j + 1, trees[i].x, trees[i].y);
        }
    }

    inf.readEof();
}

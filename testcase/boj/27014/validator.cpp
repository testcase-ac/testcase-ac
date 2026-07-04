#include "testlib.h"

#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCube = 30000;

    int p = inf.readInt(1, 100000, "P");
    inf.readEoln();

    vector<int> parent(maxCube + 1);
    for (int i = 1; i <= maxCube; ++i) {
        parent[i] = i;
    }

    for (int i = 1; i <= p; ++i) {
        char op = inf.readToken("M|C", "op")[0];
        inf.readSpace();

        if (op == 'M') {
            int x = inf.readInt(1, maxCube, "X");
            inf.readSpace();
            int y = inf.readInt(1, maxCube, "Y");
            inf.readEoln();

            int rootX = findRoot(parent, x);
            int rootY = findRoot(parent, y);
            ensuref(rootX != rootY,
                    "move operation %d moves a stack onto itself: X=%d Y=%d",
                    i, x, y);
            parent[rootX] = rootY;
        } else {
            int x = inf.readInt(1, maxCube, "X");
            inf.readEoln();
        }
    }

    inf.readEof();
}

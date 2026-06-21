#include "testlib.h"
#include <vector>
using namespace std;

static void readConfiguration(int n, const char* name) {
    vector<int> parentUsed(n + 1, 0);

    for (int child = 1; child <= n; ++child) {
        string tokenName = format("%s_%d", name, child);
        int parent = inf.readInt(0, n, tokenName.c_str());

        if (child < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }

        if (parent == 0) {
            continue;
        }

        ensuref(child < parent,
                "%s[%d] must be 0 or a larger figurine index, found %d",
                name, child, parent);
        ensuref(parentUsed[parent] == 0,
                "%s parent %d is assigned to both child %d and child %d",
                name, parent, parentUsed[parent], child);
        parentUsed[parent] = child;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    readConfiguration(n, "p");
    readConfiguration(n, "q");

    inf.readEof();
}

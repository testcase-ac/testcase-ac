#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<int> costs = inf.readInts(n, 1, 1000000, "cost");
    (void)costs;
    inf.readEoln();

    string rowPattern = "[01]{" + to_string(n) + "," + to_string(n) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "adjacency_row");
        inf.readEoln();
    }

    inf.readEof();
}

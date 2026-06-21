#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

static vector<int> readProblemList(int count, int n, const char* name) {
    vector<int> values = inf.readInts(count, 1, n, name);
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < count; ++i) {
        ensuref(seen.insert(values[i]).second,
                "%s contains duplicate value at position %d: %d",
                name, i + 1, values[i]);
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    int maxCount = min(n, 50000);
    int a = inf.readInt(1, maxCount, "A");
    inf.readSpace();
    int b = inf.readInt(1, maxCount, "B");
    inf.readEoln();

    readProblemList(a, n, "alice");
    readProblemList(b, n, "bob");

    inf.readEof();
}

#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 8, "n");
    inf.readSpace();
    int m = inf.readInt(1, 8, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 2, 10, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(m, 2, 10, "b_i");
    inf.readEoln();

    set<int> bases;
    for (int i = 0; i < n; ++i) {
        ensuref(bases.insert(a[i]).second, "duplicate base in a at index %d: %d", i + 1, a[i]);
    }
    for (int i = 0; i < m; ++i) {
        ensuref(bases.insert(b[i]).second, "duplicate base in b or across lists at index %d: %d", i + 1, b[i]);
    }

    inf.readEof();
}

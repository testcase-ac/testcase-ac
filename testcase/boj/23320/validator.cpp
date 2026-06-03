#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(10, 100, "N");
    inf.readEoln();
    ensuref(n % 10 == 0, "N must be a multiple of 10, got %d", n);

    vector<int> scores = inf.readInts(n, 1, 100, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(scores[i]).second,
                "scores must be distinct, duplicate value %d at index %d",
                scores[i], i + 1);
    }

    int x = inf.readInt(10, 100, "X");
    inf.readSpace();
    int y = inf.readInt(1, 100, "Y");
    inf.readEoln();
    ensuref(x % 10 == 0, "X must be a multiple of 10, got %d", x);

    inf.readEof();
}

#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int p = inf.readInt(0, 6, "P");
    inf.readEoln();

    int total = 100;
    for (int i = 0; i < p; ++i) {
        total *= 10;
    }

    vector<int> previous = inf.readInts(n, 0, total, "previous_i");
    inf.readEoln();
    vector<int> current = inf.readInts(n, 0, total, "current_i");
    inf.readEoln();

    ensuref(accumulate(previous.begin(), previous.end(), 0LL) == total,
            "sum of previous values must be %d", total);
    ensuref(accumulate(current.begin(), current.end(), 0LL) == total,
            "sum of current values must be %d", total);

    inf.readEof();
}

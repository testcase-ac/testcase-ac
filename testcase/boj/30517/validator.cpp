#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<int> count(1001);
    vector<int> a = inf.readInts(n, 0, 1000, "a_i");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        ++count[a[i]];
    }

    for (int value = 1; value <= 1000; ++value) {
        ensuref(count[value] == 0 || count[value] == 2,
                "nonzero value %d appears %d times", value, count[value]);
    }

    inf.readEof();
}

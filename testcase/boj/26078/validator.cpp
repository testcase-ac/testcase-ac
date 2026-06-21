#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 18, "K");
    inf.readEoln();

    int n = 1 << k;
    set<int> skills;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(1, 1000000000, "a_i");
        ensuref(skills.insert(a).second, "duplicate skill value at index %d: %d", i + 1, a);
    }
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "r_i");
    }
    inf.readEoln();

    inf.readEof();
}

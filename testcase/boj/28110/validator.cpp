#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "n");
    inf.readEoln();

    vector<int> a;
    a.reserve(n);
    set<int> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int difficulty = inf.readInt(1, 1000000000, "a_i");
        ensuref(seen.insert(difficulty).second,
                "difficulty values must be distinct, duplicate %d at index %d",
                difficulty,
                i + 1);
        a.push_back(difficulty);
    }
    inf.readEoln();
    inf.readEof();
}

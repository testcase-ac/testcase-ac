#include "testlib.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= N - 1; ++i) {
        int M_i = inf.readInt(0, N, "M_" + to_string(i));
        inf.readEoln();

        vector<int> C_i = inf.readInts(M_i, 1, N, "C_" + to_string(i));
        inf.readEoln();

        set<int> seen;
        for (int v : C_i) {
            ensuref(v != i, "self-loop at intersection %d", i);
            ensuref(seen.insert(v).second,
                    "duplicate connected intersection %d from intersection %d",
                    v,
                    i);
        }
    }

    inf.readEof();
}

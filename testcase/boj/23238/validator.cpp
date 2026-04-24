#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and q
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    // Read the list of student IDs for each day
    vector<int> a = inf.readInts(n, 1, 1000000000, "student_id");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < q; i++) {
        int S = inf.readInt(1, n, "S_i");
        inf.readSpace();
        int E = inf.readInt(1, n, "E_i");
        ensuref(S <= E,
                "S_i (%d) must be <= E_i (%d) at query index %d", 
                S, E, i);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

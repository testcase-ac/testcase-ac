#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read initial pigs in each of the M pens
    vector<int> init = inf.readInts(M, 0, 1000, "initial_pigs");
    inf.readEoln();

    // Read each customer's info
    for (int i = 1; i <= N; i++) {
        // Number of keys A_i
        int A = inf.readInt(0, M, "A_i");
        // If A>0, read A keys; otherwise skip directly to B
        set<int> seen;
        for (int j = 1; j <= A; j++) {
            inf.readSpace();
            int k = inf.readInt(1, M, "key_i_j");
            // Enforce distinct keys per customer
            ensuref(!seen.count(k),
                    "Duplicate key %d for customer %d", k, i);
            seen.insert(k);
        }
        // Read B_i
        inf.readSpace();
        // We allow B up to 1e9 (must fit in 32-bit signed)
        long long B = inf.readLong(0LL, 1000000000LL, "B_i");
        (void)B; // value checked by bounds, no further per-input constraint
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

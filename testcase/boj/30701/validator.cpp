#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int D = inf.readInt(1, 1000000000, "D");
    inf.readEoln();

    // To check equipment order, collect all equipment X_i
    vector<int> equipment_X;
    set<int> equipment_seen;

    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(1, 2, "A_i");
        inf.readSpace();
        int X = inf.readInt(2, 1000000000, "X_i");
        inf.readEoln();

        if (A == 2) {
            // Equipment
            ensuref(equipment_seen.count(X) == 0, "Duplicate equipment with X_i = %d at line %d", X, i+2);
            equipment_X.push_back(X);
            equipment_seen.insert(X);
        }
    }

    // Equipment X_i must be unique and strictly increasing order for "must get all smaller equipment before larger"
    // But the input can be in any order; the rule is about the order of acquisition, not input.
    // So, only uniqueness is required in input.

    inf.readEof();
}

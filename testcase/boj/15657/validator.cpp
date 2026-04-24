#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, 8, "M");
    ensuref(M <= N, "Constraint violated: M (%d) must be <= N (%d)", M, N);
    inf.readEoln();

    // Read the N distinct natural numbers
    vector<int> a = inf.readInts(N, 1, 10000, "a_i");
    inf.readEoln();

    // Check distinctness
    {
        set<int> s(a.begin(), a.end());
        ensuref((int)s.size() == N, "Array elements must be distinct, but found %d unique out of %d", (int)s.size(), N);
    }

    // No extra content
    inf.readEof();
    return 0;
}

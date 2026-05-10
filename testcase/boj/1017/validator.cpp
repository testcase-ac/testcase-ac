#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: even number, 2 <= N <= 50
    int N = inf.readInt(1, 50, "N");
    ensuref(N % 2 == 0, "N must be even, but N = %d", N);
    inf.readEoln();

    // Read the list of N distinct positive integers <= 1000
    vector<int> a = inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    // Check distinctness
    set<int> seen(a.begin(), a.end());
    ensuref((int)seen.size() == N,
            "All values must be distinct, but found %d unique out of %d",
            (int)seen.size(), N);

    inf.readEof();
    return 0;
}

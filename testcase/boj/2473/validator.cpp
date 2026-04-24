#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 5000, "N");
    inf.readEoln();

    // Read the N distinct solution values
    vector<long long> a = inf.readLongs(N, -1000000000LL, 1000000000LL, "a");
    inf.readEoln();

    // Check distinctness
    set<long long> seen;
    for (int i = 0; i < N; i++) {
        auto res = seen.insert(a[i]);
        ensuref(res.second,
                "Duplicate solution value at index %d: %lld", 
                i, a[i]);
    }

    inf.readEof();
    return 0;
}

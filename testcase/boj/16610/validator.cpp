#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    // Read the scores p[1..n], where p[1] is Julia's score.
    // Each must be between 0 and 10^16 inclusive.
    const long long MAXP = 10000000000000000LL; // 10^16
    vector<long long> p = inf.readLongs(n, 0LL, MAXP, "p_i");
    inf.readEoln();

    // Validate that no other bettor starts with strictly more points than Julia.
    // i.e., for all i > 1: p[i] <= p[1]
    for (int i = 1; i < n; i++) {
        ensuref(p[0] >= p[i],
                "Score of player %d (%lld) exceeds Julia's score (%lld)",
                i+1, p[i], p[0]);
    }

    inf.readEof();
    return 0;
}

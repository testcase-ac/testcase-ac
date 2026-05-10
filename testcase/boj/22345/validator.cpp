#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 2. Read N villages: a_i and x_i
    set<long long> village_positions;
    for (int i = 1; i <= N; ++i) {
        int a_i = inf.readInt(1, 1000, "a_i");
        inf.readSpace();
        long long x_i = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readEoln();

        // Check for unique x_i
        ensuref(village_positions.count(x_i) == 0,
            "Duplicate village position x_i=%lld at line %d", x_i, i+1);
        village_positions.insert(x_i);
    }

    // 3. Read Q candidate positions: q_j
    set<long long> candidate_positions;
    for (int j = 1; j <= Q; ++j) {
        long long q_j = inf.readLong(-1000000000LL, 1000000000LL, "q_j");
        inf.readEoln();

        // Check for unique q_j
        ensuref(candidate_positions.count(q_j) == 0,
            "Duplicate candidate position q_j=%lld at line %d", q_j, N+j+1);
        candidate_positions.insert(q_j);
    }

    inf.readEof();
}

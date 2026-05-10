#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read contest location (X, Y)
    long long X = inf.readLong(-1000000000LL, 1000000000LL, "X");
    inf.readSpace();
    long long Y = inf.readLong(-1000000000LL, 1000000000LL, "Y");
    inf.readEoln();

    // Read number of students N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // All positions (contest and students) must be distinct
    // Store contest location first
    set<pair<long long, long long>> used;
    used.insert({X, Y});

    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        pair<long long, long long> p = {x, y};
        ensuref(!used.count(p),
                "Duplicate position detected at student %d: (%lld, %lld)",
                i + 1, x, y);
        used.insert(p);
    }

    inf.readEof();
}

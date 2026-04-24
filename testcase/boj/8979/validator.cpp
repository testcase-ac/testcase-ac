#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Track which country indices have appeared
    vector<bool> seen(N+1, false);
    long long totalMedals = 0;

    for (int i = 1; i <= N; i++) {
        // country index
        int id = inf.readInt(1, N, "id_i");
        inf.readSpace();
        // medals
        int g = inf.readInt(0, 1000000, "gold_i");
        inf.readSpace();
        int s = inf.readInt(0, 1000000, "silver_i");
        inf.readSpace();
        int b = inf.readInt(0, 1000000, "bronze_i");
        inf.readEoln();

        // No duplicate country
        ensuref(!seen[id], "Duplicate country index %d on line %d", id, i);
        seen[id] = true;

        // Accumulate total medals
        totalMedals += (long long)g + s + b;
    }

    // Check that every country 1..N appeared exactly once
    for (int id = 1; id <= N; id++) {
        ensuref(seen[id], "Missing country index %d", id);
    }

    // Total medals constraint
    ensuref(totalMedals <= 1000000LL,
            "Sum of all medals is %lld, which exceeds 1000000", totalMedals);

    inf.readEof();
    return 0;
}

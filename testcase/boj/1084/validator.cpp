#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // 2. Read P_0 ... P_{N-1}
    vector<long long> P(N);
    set<long long> pset;
    for (int i = 0; i < N; ++i) {
        P[i] = inf.readLong(1LL, 1000000000000000000LL, "P_i");
        pset.insert(P[i]);
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read M
    long long M = inf.readLong(0LL, 1000000000000000000LL, "M");
    inf.readEoln();

    // 4. No extra lines
    inf.readEof();

    // 5. Additional global checks (implied by problem statement):

    // - All P_i are in range [1, 1e18] (already checked)
    // - N in [1,10] (already checked)
    // - M in [0,1e18] (already checked)
    // - No further global constraints (e.g., no requirement for unique P_i, etc.)

    // 6. Implied property: "문방구에서는 같은 숫자를 여러 개 구매할 수 있고, 문방구는 매우 많은 재고를 보유하고 있기 때문에, 항상 원하는 만큼 숫자를 구매할 수 있다."
    //    - No need to check for stock or uniqueness.

    // 7. No further global property to check (e.g., answer always exists is not an input property, but a solution property).

    // 8. Formatting: already enforced by readEoln and readEof.

    return 0;
}

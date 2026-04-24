#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 <= T <= 100
    int T = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        inf.setTestCase(tc);

        // Number of players: 1 <= p <= 100
        int p = inf.readInt(1, 100, "p");
        inf.readEoln();

        // Track seen prices to enforce uniqueness
        set<long long> prices;

        for (int i = 1; i <= p; i++) {
            // Read price C: 0 <= C < 2*10^9
            long long c = inf.readLong(0LL, 2000000000LL - 1, "price");
            // Exactly one space before the name
            inf.readSpace();
            // Read player name: no spaces, length 1..20
            inf.readToken("[^ ]{1,20}", "name");
            // End of line
            inf.readEoln();

            // Ensure all prices are distinct within this test case
            bool inserted = prices.insert(c).second;
            ensuref(inserted,
                    "Duplicate price %lld in test case %d at player index %d",
                    c, tc, i);
        }
    }

    inf.readEof();
    return 0;
}

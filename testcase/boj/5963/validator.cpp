#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<long long> factorial(21, 1);
    for (int i = 1; i <= 20; ++i) {
        factorial[i] = factorial[i - 1] * i;
    }

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();

    for (int query = 1; query <= k; ++query) {
        setTestCase(query);

        string command = inf.readToken("P|Q", "C_i");
        inf.readEoln();

        if (command == "P") {
            inf.readLong(1LL, factorial[n], "A_i");
            inf.readEoln();
        } else {
            set<int> seen;
            for (int j = 1; j <= n; ++j) {
                int cow = inf.readInt(1, n, "B_ij");
                ensuref(seen.insert(cow).second,
                        "duplicate cow in query %d at position %d: %d",
                        query, j, cow);
                if (j < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}

#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        set<int> seen;
        int lands = 0;

        while (true) {
            // CHECK: The statement omits an upper bound for land prices; cap at
            // int-scale values while keeping all useful answer cases representable.
            int price = inf.readInt(0, 1000000000, "L_i");
            inf.readEoln();

            if (price == 0) {
                break;
            }

            // CHECK: Land prices are costs, so only the terminating sentinel may be zero.
            ensuref(price > 0, "land price must be positive, got %d", price);
            ensuref(seen.insert(price).second, "duplicate land price: %d", price);
            ++lands;

            // CHECK: Korean statement says at most 40 lands; the English variant says
            // less than 40. Follow the primary statement for this BOJ problem.
            ensuref(lands <= 40, "too many lands in test case: %d", lands);
        }

        // CHECK: A test case describes lands to buy, so reject an empty case.
        ensuref(lands >= 1, "test case must contain at least one land price");
    }

    inf.readEof();
}

#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        inf.readInt(100, 500, "M");
        inf.readEoln();

        set<int> prices;
        for (int i = 1; i <= 12; ++i) {
            int p = inf.readInt(1, 250, "P_i");
            ensuref(prices.insert(p).second,
                    "monthly prices must be distinct, duplicate price %d at month %d",
                    p,
                    i);
            if (i < 12) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}

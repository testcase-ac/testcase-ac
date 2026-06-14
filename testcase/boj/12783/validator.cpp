#include "testlib.h"
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10, "N");
        set<int> cards;
        for (int i = 1; i <= n; ++i) {
            inf.readSpace();
            int card = inf.readInt(0, 9, "card");
            ensuref(cards.insert(card).second,
                    "duplicate card kind in test case %d: %d", tc, card);
        }
        inf.readEoln();

        int m = inf.readInt(1, 20, "M");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, 1000000, "K");
            inf.readEoln();
        }
    }

    inf.readEof();
}

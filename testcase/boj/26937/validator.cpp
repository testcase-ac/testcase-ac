#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 15, "M");
    inf.readEoln();

    vector<bool> covered(n + 1, false);
    for (int store = 1; store <= m; ++store) {
        // CHECK: The statement does not give a lower bound for K. A bookstore
        // can list zero sought books as long as every book is available
        // somewhere overall.
        int k = inf.readInt(0, n, "K");
        inf.readSpace();
        inf.readInt(0, 10000, "postage");
        inf.readEoln();

        vector<bool> seenInStore(n + 1, false);
        for (int item = 1; item <= k; ++item) {
            int book = inf.readInt(1, n, "book");
            inf.readSpace();
            inf.readInt(1, 10000, "price");
            inf.readEoln();

            ensuref(!seenInStore[book],
                    "book %d appears more than once in store %d",
                    book,
                    store);
            seenInStore[book] = true;
            covered[book] = true;
        }
    }

    for (int book = 1; book <= n; ++book) {
        ensuref(covered[book], "book %d is not available in any bookstore", book);
    }

    inf.readEof();
}

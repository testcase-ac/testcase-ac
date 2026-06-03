#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    string queries = inf.readToken("[a-z-]{1,10000}", "K");
    ensuref(static_cast<int>(queries.size()) == q,
            "query string length must be Q: expected %d, got %d",
            q,
            static_cast<int>(queries.size()));
    inf.readEoln();

    int length = 0;
    for (int i = 0; i < q; ++i) {
        if (queries[i] == '-') {
            --length;
        } else {
            ++length;
        }
        ensuref(length >= 1,
                "string length must be positive after query %d",
                i + 1);
    }

    inf.readEof();
}

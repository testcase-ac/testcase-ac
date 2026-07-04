#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    long long totalChars = 0;
    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 100, "m");
        inf.readEoln();

        string z = inf.readToken("[A-Za-z]{1,1000}", "z");
        inf.readEoln();
        totalChars += z.size();

        for (int i = 1; i <= m; ++i) {
            string y = inf.readToken("[A-Za-z]{1,1000}", "y_i");
            inf.readEoln();
            totalChars += y.size();
        }

        // CHECK: The statement gives K >= 1 but no upper bound. Cap the total
        // string payload to one largest practical dataset scale.
        ensuref(totalChars <= 101000LL,
                "total string payload exceeds 101000 characters at dataset %d",
                tc);
    }

    inf.readEof();
    return 0;
}

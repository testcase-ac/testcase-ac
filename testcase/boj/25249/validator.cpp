#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, 100000, "m");
    inf.readEoln();

    vector<int> connectionCount(n, 0);
    for (int edge = 1; edge <= m; ++edge) {
        int city = inf.readInt(1, n - 1, "i");
        inf.readSpace();
        inf.readInt(1, 10000, "d");
        inf.readSpace();
        inf.readInt(1, 1000000, "c");
        inf.readEoln();

        ++connectionCount[city];
    }

    for (int city = 1; city < n; ++city) {
        ensuref(connectionCount[city] > 0,
                "no connection from city %d to city %d", city, city + 1);
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();
    for (int query = 1; query <= q; ++query) {
        inf.readInt(1, 1000000, "w_i");
        inf.readEoln();
    }

    inf.readEof();
}

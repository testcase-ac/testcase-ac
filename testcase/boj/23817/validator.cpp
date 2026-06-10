#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(4, 1000, "M");
    inf.readEoln();

    int startCount = 0;
    int restaurantCount = 0;
    string rowPattern = "[.XSK]{" + to_string(m) + "," + to_string(m) + "}";

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken(rowPattern, "row");
        inf.readEoln();

        for (int j = 0; j < m; ++j) {
            if (row[j] == 'S') {
                ++startCount;
            } else if (row[j] == 'K') {
                ++restaurantCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one S, found %d", startCount);
    ensuref(1 <= restaurantCount && restaurantCount <= 20,
            "expected 1 to 20 K cells, found %d", restaurantCount);

    inf.readEof();
}

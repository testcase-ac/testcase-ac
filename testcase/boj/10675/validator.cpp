#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 10000, "B");
    inf.readSpace();
    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int route = 1; route <= n; ++route) {
        int cost = inf.readInt(1, 1000, "cost");
        inf.readSpace();
        int cityCount = inf.readInt(2, 500, "city_count");
        inf.readEoln();

        set<int> seen;
        for (int i = 1; i <= cityCount; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            int city = inf.readInt(1, 10000, "city");
            ensuref(seen.insert(city).second,
                    "city %d appears multiple times in route %d", city, route);
        }
        inf.readEoln();
    }

    inf.readEof();
}

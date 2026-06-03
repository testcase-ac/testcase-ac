#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 1000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 1000, "B");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int route = 1; route <= n; ++route) {
        long long cost = inf.readLong(1LL, 1000000000LL, "cost");
        inf.readSpace();
        int city_count = inf.readInt(2, 100, "city_count");
        inf.readEoln();

        set<int> seen;
        for (int i = 1; i <= city_count; ++i) {
            int city = inf.readInt(1, 1000, "city");
            ensuref(seen.insert(city).second,
                    "city %d appears multiple times in route %d", city, route);
            if (i < city_count) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        (void)cost;
    }

    (void)a;
    (void)b;
    inf.readEof();
}

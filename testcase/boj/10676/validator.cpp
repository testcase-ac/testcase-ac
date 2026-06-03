#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 10000, "B");
    inf.readSpace();
    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int cost = inf.readInt(1, 1000, "cost");
        inf.readSpace();
        int routeLength = inf.readInt(2, 500, "route_length");
        inf.readEoln();

        vector<int> cities = inf.readInts(routeLength, 1, 10000, "city");
        inf.readEoln();

        set<int> seen;
        for (int city : cities) {
            ensuref(seen.insert(city).second,
                    "city %d appears multiple times in route %d", city, i + 1);
        }
    }

    inf.readEof();
}

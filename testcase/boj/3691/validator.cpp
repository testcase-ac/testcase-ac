#include "testlib.h"

#include <map>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = inf.readInt(1, 100, "tc");
    inf.readEoln();

    for (int t = 1; t <= tc; ++t) {
        setTestCase(t);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        long long budget = inf.readLong(1LL, 1000000000LL, "b");
        inf.readEoln();

        set<string> names;
        map<string, int> minPriceByType;

        for (int i = 1; i <= n; ++i) {
            string type = inf.readToken("[A-Za-z0-9_]{1,20}", "type");
            inf.readSpace();
            string name = inf.readToken("[A-Za-z0-9_]{1,20}", "name");
            inf.readSpace();
            int price = inf.readInt(0, 1000000, "price");
            inf.readSpace();
            inf.readInt(0, 1000000000, "quality");
            inf.readEoln();

            ensuref(names.insert(name).second,
                    "duplicate component name in testcase %d at item %d: %s",
                    t, i, name.c_str());

            auto it = minPriceByType.find(type);
            if (it == minPriceByType.end()) {
                minPriceByType[type] = price;
            } else if (price < it->second) {
                it->second = price;
            }
        }

        long long cheapestBuild = 0;
        for (const auto& [type, price] : minPriceByType) {
            cheapestBuild += price;
        }

        ensuref(cheapestBuild <= budget,
                "testcase %d cannot be assembled within budget: cheapest=%lld budget=%lld",
                t, cheapestBuild, budget);
    }

    inf.readEof();
}

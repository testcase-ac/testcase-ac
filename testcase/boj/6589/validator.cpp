#include "testlib.h"

#include <set>
#include <string>

using namespace std;

namespace {

string readCityName(const char* name) {
    return inf.readToken("[^]{1,30}", name);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxCases = 100000;  // CHECK: statement gives no case-count bound.

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 200, "n");
        inf.readSpace();
        int r = inf.readInt(0, 19900, "r");
        inf.readEoln();

        if (n == 0 && r == 0) {
            break;
        }

        ++cases;
        setTestCase(cases);
        ensuref(cases <= kMaxCases, "too many test cases: %d", cases);
        ensuref(2 <= n, "n must be at least 2 in a non-terminal case: %d", n);
        ensuref(1 <= r, "r must be at least 1 in a non-terminal case: %d", r);

        set<string> cities;
        for (int i = 1; i <= r; ++i) {
            string a = readCityName("city_a");
            inf.readSpace();
            string b = readCityName("city_b");
            inf.readSpace();
            inf.readInt(0, 10000, "weight_limit");
            inf.readEoln();

            ensuref(a != b, "road %d is a self-loop on city %s", i, a.c_str());
            cities.insert(a);
            cities.insert(b);
            ensuref(static_cast<int>(cities.size()) <= n,
                    "more than n city names appear in case %d", cases);
        }

        string start = readCityName("start");
        inf.readSpace();
        string destination = readCityName("destination");
        inf.readEoln();

        cities.insert(start);
        cities.insert(destination);
        ensuref(static_cast<int>(cities.size()) <= n,
                "more than n city names appear after query in case %d", cases);
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

long long readChange() {
    string token = inf.readToken("[+-][1-9][0-9]{0,9}", "change");
    long long value = stoll(token);
    ensuref(value >= -1000000000LL && value <= 1000000000LL,
            "change is outside possible milk-output delta range: %lld", value);
    ensuref(value != 0, "change must be nonzero");
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long g = inf.readLong(1LL, 1000000000LL, "G");
    inf.readEoln();

    vector<tuple<int, int, long long>> measurements;
    measurements.reserve(n);
    set<int> days;

    for (int i = 0; i < n; ++i) {
        int day = inf.readInt(1, 1000000, "day");
        inf.readSpace();
        int cow = inf.readInt(1, 1000000000, "cow");
        inf.readSpace();
        long long change = readChange();
        inf.readEoln();

        ensuref(days.insert(day).second, "multiple measurements on day %d", day);
        measurements.emplace_back(day, cow, change);
    }

    sort(measurements.begin(), measurements.end());

    map<int, long long> milk;
    for (const auto& [day, cow, change] : measurements) {
        long long before = milk.count(cow) ? milk[cow] : g;
        long long after = before + change;
        ensuref(0LL <= after && after <= 1000000000LL,
                "cow %d output on day %d is outside [0, 1e9]: %lld",
                cow, day, after);
        milk[cow] = after;
    }

    inf.readEof();
}

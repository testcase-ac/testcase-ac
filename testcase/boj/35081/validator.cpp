#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    set<long long> eventTimes;
    vector<vector<pair<long long, long long>>> tripsByPerson(n + 1);

    for (int i = 1; i <= q; ++i) {
        int p = inf.readInt(1, n, "p");
        inf.readSpace();
        long long l = inf.readLong(0LL, 1000000000LL, "l");
        inf.readSpace();
        long long r = inf.readLong(0LL, 1000000000LL, "r");
        inf.readEoln();

        ensuref(l < r, "trip %d has l >= r: %lld >= %lld", i, l, r);
        ensuref(eventTimes.insert(l).second, "duplicate event time at trip %d: %lld", i, l);
        ensuref(eventTimes.insert(r).second, "duplicate event time at trip %d: %lld", i, r);
        tripsByPerson[p].push_back({l, r});
    }

    for (int p = 1; p <= n; ++p) {
        auto& trips = tripsByPerson[p];
        sort(trips.begin(), trips.end());
        for (int i = 1; i < static_cast<int>(trips.size()); ++i) {
            ensuref(trips[i - 1].second < trips[i].first,
                    "trips for person %d touch or overlap: [%lld, %lld] and [%lld, %lld]",
                    p,
                    trips[i - 1].first,
                    trips[i - 1].second,
                    trips[i].first,
                    trips[i].second);
        }
    }

    inf.readEof();
}

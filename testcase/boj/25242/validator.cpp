#include "testlib.h"

#include <map>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    long long totalStations = 0;
    map<string, int> stationLineCount;
    set<string> allStations;

    for (int line = 1; line <= n; ++line) {
        int s = inf.readInt(2, 200000, "s");
        totalStations += s;
        ensuref(totalStations <= 200000,
                "total station occurrences exceed 200000 after line %d", line);

        set<string> stationsOnLine;
        for (int i = 1; i <= s; ++i) {
            inf.readSpace();
            string station = inf.readToken("[A-Za-z]{1,8}", "station");
            ensuref(stationsOnLine.insert(station).second,
                    "duplicate station on line %d: %s", line, station.c_str());
        }
        inf.readEoln();

        for (const string& station : stationsOnLine) {
            ++stationLineCount[station];
            allStations.insert(station);
        }
    }

    int transferStations = 0;
    for (const auto& entry : stationLineCount) {
        if (entry.second >= 2) {
            ++transferStations;
        }
    }
    ensuref(transferStations <= 20, "transfer station count is %d", transferStations);

    for (int query = 1; query <= q; ++query) {
        string from = inf.readToken("[A-Za-z]{1,8}", "from");
        inf.readSpace();
        string to = inf.readToken("[A-Za-z]{1,8}", "to");
        inf.readEoln();

        // CHECK: The statement calls these departure/destination stations; reject
        // names that are not present in the described subway network.
        ensuref(allStations.count(from) != 0,
                "query %d has unknown departure station: %s", query, from.c_str());
        ensuref(allStations.count(to) != 0,
                "query %d has unknown destination station: %s", query, to.c_str());
    }

    inf.readEof();
}

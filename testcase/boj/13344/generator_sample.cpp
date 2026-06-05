#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Report {
    int a;
    char op;
    int b;
};

pair<int, int> normalizedPair(int a, int b) {
    if (a > b) swap(a, b);
    return {a, b};
}

bool addReport(vector<Report>& reports, set<pair<int, int>>& usedPairs, int a, char op, int b) {
    if (a == b) return false;
    if (!usedPairs.insert(normalizedPair(a, b)).second) return false;
    reports.push_back({a, op, b});
    return true;
}

void addComparison(vector<Report>& reports, set<pair<int, int>>& usedPairs, int stronger, int weaker) {
    addReport(reports, usedPairs, stronger, '>', weaker);
}

void coverIsolatedPlayers(vector<Report>& reports, set<pair<int, int>>& usedPairs, int n) {
    vector<bool> seen(n, false);
    for (const Report& report : reports) {
        seen[report.a] = true;
        seen[report.b] = true;
    }

    for (int player = 0; player < n; ++player) {
        if (seen[player]) continue;

        int other = player == 0 ? 1 : player - 1;
        char op = rnd.any(string("=>"));
        addReport(reports, usedPairs, player, op, other);
        seen[player] = true;
        seen[other] = true;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 12);
    vector<Report> reports;
    set<pair<int, int>> usedPairs;

    if (mode == 0) {
        vector<int> players(n);
        for (int i = 0; i < n; ++i) players[i] = i;
        shuffle(players.begin(), players.end());

        int groupCount = rnd.next(1, min(n, 5));
        vector<vector<int>> groups(groupCount);
        for (int i = 0; i < n; ++i) groups[i % groupCount].push_back(players[i]);

        for (const vector<int>& group : groups) {
            for (int i = 1; i < int(group.size()); ++i) {
                addReport(reports, usedPairs, group[i - 1], '=', group[i]);
            }
        }

        for (int high = 0; high < groupCount; ++high) {
            for (int low = high + 1; low < groupCount; ++low) {
                if (rnd.next(100) < 55) {
                    addComparison(reports, usedPairs, rnd.any(groups[high]), rnd.any(groups[low]));
                }
            }
        }
    } else if (mode == 1) {
        n = max(n, 3);
        vector<int> cycle = {0, 1, 2};
        shuffle(cycle.begin(), cycle.end());
        addComparison(reports, usedPairs, cycle[0], cycle[1]);
        addComparison(reports, usedPairs, cycle[1], cycle[2]);
        addComparison(reports, usedPairs, cycle[2], cycle[0]);
    } else if (mode == 2) {
        n = max(n, 3);
        vector<int> trio = {0, 1, 2};
        shuffle(trio.begin(), trio.end());
        addReport(reports, usedPairs, trio[0], '=', trio[1]);
        addReport(reports, usedPairs, trio[1], '=', trio[2]);
        addComparison(reports, usedPairs, trio[2], trio[0]);
    } else {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        for (int i = 1; i < n; ++i) {
            if (rnd.next(100) < 35) {
                addReport(reports, usedPairs, order[i - 1], '=', order[i]);
            } else {
                addComparison(reports, usedPairs, order[i - 1], order[i]);
            }
        }

        int extra = rnd.next(0, min(12, n * (n - 1) / 2 - int(reports.size())));
        for (int tries = 0; tries < 80 && extra > 0; ++tries) {
            int i = rnd.next(n);
            int j = rnd.next(n);
            if (i == j) continue;

            char op = rnd.any(string("=>"));
            if (addReport(reports, usedPairs, i, op, j)) --extra;
        }
    }

    coverIsolatedPlayers(reports, usedPairs, n);
    shuffle(reports.begin(), reports.end());

    println(n, int(reports.size()));
    for (const Report& report : reports) {
        println(report.a, string(1, report.op), report.b);
    }

    return 0;
}

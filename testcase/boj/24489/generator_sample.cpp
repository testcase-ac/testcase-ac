#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Road {
    int x;
    int y;
    bool removed;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(4, 12);
    }

    int maxQ = min(35, 3 * n + 12);
    int targetQ = mode == 0 ? rnd.next(0, max(0, n + 2)) : rnd.next(n, maxQ);

    vector<bool> active(n + 1, true);
    vector<int> activeNodes;
    vector<Road> roads(1, {0, 0, true});
    vector<string> operations;

    auto refreshActiveNodes = [&]() {
        activeNodes.clear();
        for (int i = 1; i <= n; ++i) {
            if (active[i]) activeNodes.push_back(i);
        }
    };

    auto canAdd = [&]() {
        refreshActiveNodes();
        return (int)activeNodes.size() >= 2;
    };

    auto removableRoadIds = [&]() {
        vector<int> ids;
        for (int i = 1; i < (int)roads.size(); ++i) {
            if (!roads[i].removed) ids.push_back(i);
        }
        return ids;
    };

    while ((int)operations.size() < targetQ) {
        refreshActiveNodes();
        vector<int> choices;
        if ((int)activeNodes.size() >= 2) choices.push_back(0);
        if (!activeNodes.empty()) choices.push_back(1);
        if (!removableRoadIds().empty()) choices.push_back(2);
        if (choices.empty()) break;

        int op = rnd.any(choices);
        if (mode == 1 && canAdd()) op = 0;
        if (mode == 2 && !removableRoadIds().empty() && rnd.next(0, 2) != 0) op = 2;
        if (mode == 3 && !activeNodes.empty() && rnd.next(0, 2) != 0) op = 1;

        if (op == 0 && (int)activeNodes.size() >= 2) {
            int x = rnd.any(activeNodes);
            int y = rnd.any(activeNodes);
            while (y == x) y = rnd.any(activeNodes);
            if (mode == 4 && !roads.empty() && rnd.next(0, 3) == 0) {
                for (int i = 1; i < (int)roads.size(); ++i) {
                    if (active[roads[i].x] && active[roads[i].y]) {
                        x = roads[i].x;
                        y = roads[i].y;
                        break;
                    }
                }
            }
            roads.push_back({x, y, false});
            operations.push_back("A " + toString(x) + " " + toString(y));
        } else if (op == 1 && !activeNodes.empty()) {
            int x = rnd.any(activeNodes);
            active[x] = false;
            operations.push_back("D " + toString(x));
        } else {
            vector<int> ids = removableRoadIds();
            if (ids.empty()) continue;
            int e = rnd.any(ids);
            roads[e].removed = true;
            operations.push_back("R " + toString(e));
        }
    }

    println(n, (int)operations.size());
    for (const string& operation : operations) {
        println(operation);
    }

    return 0;
}

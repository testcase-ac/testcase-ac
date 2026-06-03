#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    int bridgeCount = rnd.next(1, 5);
    int q = rnd.next(1, 12);

    int firstHospital = n + 1;
    int firstBridge = n + m + 1;
    int totalNodes = n + m + bridgeCount;

    vector<Edge> edges;
    auto addEdge = [&](int a, int b, int lo = 1, int hi = 50) {
        edges.push_back({a, b, rnd.next(lo, hi)});
    };

    if (mode == 0) {
        int bridge = firstBridge + rnd.next(0, bridgeCount - 1);
        for (int house = 1; house <= n; ++house) {
            if (rnd.next(0, 99) < 80) addEdge(house, bridge);
        }
        for (int hospital = firstHospital; hospital < firstHospital + m; ++hospital) {
            if (rnd.next(0, 99) < 80) addEdge(hospital, bridge);
        }
    } else if (mode == 1) {
        int houseLimit = rnd.next(1, n);
        int hospitalLimit = rnd.next(1, m);
        int bridge = firstBridge;
        for (int house = 1; house <= houseLimit; ++house) addEdge(house, bridge, 1, 20);
        for (int i = 0; i < hospitalLimit; ++i) addEdge(firstHospital + i, bridge, 1, 20);
    } else if (mode == 2) {
        int node = rnd.next(1, totalNodes);
        addEdge(node, node, 1, 10);

        int bridge = firstBridge + rnd.next(0, bridgeCount - 1);
        int house = rnd.next(1, n);
        int hospital = firstHospital + rnd.next(0, m - 1);
        addEdge(house, bridge, 1, 30);
        addEdge(house, bridge, 1, 30);
        addEdge(hospital, bridge, 1, 30);
        addEdge(hospital, bridge, 1, 30);
    } else if (mode == 3) {
        vector<int> bridges;
        for (int i = 0; i < bridgeCount; ++i) bridges.push_back(firstBridge + i);
        shuffle(bridges.begin(), bridges.end());

        addEdge(rnd.next(1, n), bridges.front(), 1, 25);
        for (int i = 1; i < bridgeCount; ++i) addEdge(bridges[i - 1], bridges[i], 1, 25);
        addEdge(firstHospital + rnd.next(0, m - 1), bridges.back(), 1, 25);
    } else {
        int extra = rnd.next(1, min(12, n + m + bridgeCount));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(1, totalNodes);
            int b = rnd.next(1, totalNodes);
            bool aHouse = a <= n;
            bool bHouse = b <= n;
            bool aHospital = n < a && a <= n + m;
            bool bHospital = n < b && b <= n + m;
            if ((aHouse && bHospital) || (aHospital && bHouse)) {
                b = firstBridge + rnd.next(0, bridgeCount - 1);
            }
            addEdge(a, b, 1, 100);
        }
    }

    while ((int)edges.size() < rnd.next(1, 4)) {
        int bridge = firstBridge + rnd.next(0, bridgeCount - 1);
        if (rnd.next(0, 1) == 0) {
            addEdge(rnd.next(1, n), bridge, 1, 40);
        } else {
            addEdge(firstHospital + rnd.next(0, m - 1), bridge, 1, 40);
        }
    }

    vector<pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int s = rnd.next(1, n);
        int e = firstHospital + rnd.next(0, m - 1);
        queries.push_back({s, e});
    }

    println(n, m, bridgeCount, (int)edges.size(), q);
    for (const Edge& edge : edges) println(edge.a, edge.b, edge.w);
    for (const auto& query : queries) println(query.first, query.second);

    return 0;
}

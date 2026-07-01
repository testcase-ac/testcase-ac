#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

struct Place {
    int floor;
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 16);
    int floorMax = rnd.next(1, 5);
    int coordMax = rnd.next(4, 30);

    vector<Place> places(n);
    for (int i = 0; i < n; ++i) {
        places[i] = {rnd.next(0, floorMax), rnd.next(0, coordMax), rnd.next(0, coordMax)};
    }

    if (mode == 1) {
        int floor = rnd.next(0, floorMax);
        for (auto& place : places) place.floor = floor;
    } else if (mode == 2) {
        int x = rnd.next(0, coordMax);
        int y = rnd.next(0, coordMax);
        for (auto& place : places) {
            place.x = x;
            place.y = y;
        }
    }

    vector<tuple<int, int, string>> edges;
    set<pair<int, int>> seen;

    auto edgeType = [&](int a, int b) {
        if (places[a].floor == places[b].floor) return string("walking");
        vector<string> types = {"stairs", "lift", "escalator"};
        return rnd.any(types);
    };

    auto addEdge = [&](int a, int b) {
        if (a == b) return false;
        auto key = minmax(a, b);
        if (!seen.insert(key).second) return false;
        edges.emplace_back(a, b, edgeType(a, b));
        return true;
    };

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());
    for (int i = 1; i < n; ++i) {
        int a = order[i];
        int b = order[rnd.next(0, i - 1)];
        addEdge(a, b);
    }

    int maxEdges = n * (n - 1) / 2;
    int extraLimit = max(0, min(maxEdges - (int)edges.size(), rnd.next(0, n + 4)));
    for (int attempts = 0; attempts < 5 * max(1, n) && (int)edges.size() < n - 1 + extraLimit; ++attempts) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        addEdge(a, b);
    }

    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, min(30, max(1, n * 3)));
    vector<pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int a = rnd.next(0, n - 1);
        int b = (rnd.next(0, 4) == 0) ? a : rnd.next(0, n - 1);
        queries.emplace_back(a, b);
    }

    println(n, (int)edges.size());
    for (const auto& place : places) {
        println(place.floor, place.x, place.y);
    }
    for (const auto& [a, b, type] : edges) {
        println(a, b, type);
    }
    println(q);
    for (const auto& [a, b] : queries) {
        println(a, b);
    }

    return 0;
}

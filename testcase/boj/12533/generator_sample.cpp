#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Case {
    int n;
    vector<pair<int, int>> roads;
};

pair<int, int> road(int a, int b) {
    if (rnd.next(2)) swap(a, b);
    return {a, b};
}

void addRoad(vector<pair<int, int>>& roads, int a, int b) {
    roads.push_back(road(a, b));
}

Case makeParallelCase() {
    int n = rnd.next(2, 12);
    int a = rnd.next(0, n - 1);
    int b = rnd.next(0, n - 2);
    if (b >= a) ++b;

    int r = rnd.next(1, 15);
    vector<pair<int, int>> roads;
    for (int i = 0; i < r; ++i) addRoad(roads, a, b);
    return {n, roads};
}

Case makeCycleCase() {
    int n = rnd.next(3, 14);
    int len = rnd.next(3, min(n, 10));

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    shuffle(vertices.begin(), vertices.end());
    vertices.resize(len);

    vector<pair<int, int>> roads;
    for (int i = 0; i < len; ++i) {
        addRoad(roads, vertices[i], vertices[(i + 1) % len]);
    }

    int extraPairs = rnd.next(0, (15 - len) / 2);
    for (int i = 0; i < extraPairs; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        addRoad(roads, a, b);
        addRoad(roads, a, b);
    }

    shuffle(roads.begin(), roads.end());
    return {n, roads};
}

Case makePathCase() {
    int n = rnd.next(2, 16);
    int len = rnd.next(1, min(15, n - 1));

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    shuffle(vertices.begin(), vertices.end());

    vector<pair<int, int>> roads;
    for (int i = 0; i < len; ++i) addRoad(roads, vertices[i], vertices[i + 1]);
    return {n, roads};
}

Case makeDisconnectedCase() {
    int components = rnd.next(2, 5);
    int n = rnd.next(max(components * 2, 4), 20);

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    shuffle(vertices.begin(), vertices.end());

    vector<pair<int, int>> roads;
    int cursor = 0;
    for (int c = 0; c < components && static_cast<int>(roads.size()) < 15; ++c) {
        int remaining = n - cursor;
        int needAfter = (components - c - 1) * 2;
        int size = rnd.next(2, min(5, remaining - needAfter));
        vector<int> part(vertices.begin() + cursor, vertices.begin() + cursor + size);
        cursor += size;

        int localRoads = rnd.next(1, min(4, 15 - static_cast<int>(roads.size())));
        for (int i = 0; i < localRoads; ++i) {
            int a = rnd.any(part);
            int b = rnd.any(part);
            while (b == a) b = rnd.any(part);
            addRoad(roads, a, b);
        }
    }

    shuffle(roads.begin(), roads.end());
    return {n, roads};
}

Case makeStarCase() {
    int n = rnd.next(3, 18);
    int center = rnd.next(0, n - 1);
    int r = rnd.next(2, min(15, n - 1));

    vector<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (i != center) leaves.push_back(i);
    }
    shuffle(leaves.begin(), leaves.end());

    vector<pair<int, int>> roads;
    for (int i = 0; i < r; ++i) addRoad(roads, center, leaves[i]);
    return {n, roads};
}

Case makeHighLabelCase() {
    int n = rnd.next(900, 1000);
    int active = rnd.next(2, 8);

    vector<int> vertices;
    vertices.push_back(0);
    vertices.push_back(n - 1);
    while (static_cast<int>(vertices.size()) < active) {
        int v = rnd.next(1, n - 2);
        if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
            vertices.push_back(v);
        }
    }

    int r = rnd.next(1, 15);
    vector<pair<int, int>> roads;
    for (int i = 0; i < r; ++i) {
        int a = rnd.any(vertices);
        int b = rnd.any(vertices);
        while (b == a) b = rnd.any(vertices);
        addRoad(roads, a, b);
    }
    return {n, roads};
}

Case makeRandomCase() {
    int n = rnd.next(2, 20);
    int r = rnd.next(1, 15);

    vector<pair<int, int>> roads;
    for (int i = 0; i < r; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        addRoad(roads, a, b);
    }
    return {n, roads};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 6);
        Case cur;
        if (mode == 0) cur = makeParallelCase();
        else if (mode == 1) cur = makeCycleCase();
        else if (mode == 2) cur = makePathCase();
        else if (mode == 3) cur = makeDisconnectedCase();
        else if (mode == 4) cur = makeStarCase();
        else if (mode == 5) cur = makeHighLabelCase();
        else cur = makeRandomCase();

        println(cur.n);
        println(static_cast<int>(cur.roads.size()));
        for (auto [a, b] : cur.roads) println(a, b);
    }

    return 0;
}

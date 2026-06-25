#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Road {
    int a;
    int b;
};

static void addRoad(vector<Road>& roads, int a, int b) {
    if (a > b) swap(a, b);
    roads.push_back({a, b});
}

static void addPath(vector<Road>& roads, int first, int length) {
    for (int i = 0; i < length; ++i) {
        addRoad(roads, first + i, first + i + 1);
    }
}

static vector<Road> connectedOddMix(int n) {
    vector<Road> roads;
    addPath(roads, 0, n - 1);

    for (int i = 0; i + 2 < n; i += 2) {
        if (rnd.next(2) == 0) addRoad(roads, i, i + 2);
    }

    if (n >= 4 && rnd.next(3) == 0) {
        int a = rnd.next(0, n - 2);
        int b = rnd.next(a + 1, n - 1);
        addRoad(roads, a, b);
    }

    return roads;
}

static vector<Road> eulerianCycleWithParallels(int n) {
    vector<Road> roads;
    for (int i = 0; i < n; ++i) {
        addRoad(roads, i, (i + 1) % n);
    }

    int pairs = rnd.next(1, 3);
    for (int i = 0; i < pairs; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        addRoad(roads, a, b);
        addRoad(roads, a, b);
    }

    return roads;
}

static vector<Road> disconnectedComponents(int n) {
    vector<Road> roads;
    int cursor = 0;
    while (cursor < n - 1) {
        int remaining = n - cursor;
        int size = rnd.next(2, min(4, remaining));
        if (cursor + size > n) size = n - cursor;

        if (size == 2 || rnd.next(2) == 0) {
            int copies = rnd.next(1, 3);
            for (int i = 0; i < copies; ++i) addRoad(roads, cursor, cursor + 1);
        } else {
            for (int i = 0; i < size; ++i) {
                addRoad(roads, cursor + i, cursor + (i + 1) % size);
            }
        }

        cursor += size;
        if (cursor < n && rnd.next(3) == 0) ++cursor;
    }

    if (roads.empty()) addRoad(roads, 0, 1);
    return roads;
}

static vector<Road> sparseRandomMultigraph(int n) {
    vector<Road> roads;
    set<pair<int, int>> usedSimple;
    int simpleEdges = rnd.next(1, min(2 * n, n * (n - 1) / 2));
    while ((int)usedSimple.size() < simpleEdges) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        if (a > b) swap(a, b);
        usedSimple.insert({a, b});
    }

    for (auto [a, b] : usedSimple) {
        int copies = rnd.next(1, rnd.next(1, 3));
        for (int i = 0; i < copies; ++i) addRoad(roads, a, b);
    }

    return roads;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(4);
        int n = rnd.next(2, 12);
        vector<Road> roads;

        if (mode == 0) {
            roads = connectedOddMix(n);
        } else if (mode == 1) {
            n = max(n, 3);
            roads = eulerianCycleWithParallels(n);
        } else if (mode == 2) {
            n = max(n, 4);
            roads = disconnectedComponents(n);
        } else {
            roads = sparseRandomMultigraph(n);
        }

        shuffle(roads.begin(), roads.end());
        println(n);
        println((int)roads.size());
        for (const Road& road : roads) {
            println(road.a, road.b);
        }
    }

    return 0;
}

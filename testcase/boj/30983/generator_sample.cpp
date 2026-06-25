#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Road {
    int type;
    int a;
    int b;
    int c;
};

Road makePairRoad(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;
    if (rnd.next(2)) swap(a, b);
    return {1, a, b, 0};
}

Road makeTripleRoad(int n) {
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) nodes.push_back(i);
    shuffle(nodes.begin(), nodes.end());
    return {2, nodes[0], nodes[1], nodes[2]};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 4 ? 14 : 9);
    int m = rnd.next(1, mode == 4 ? 60 : 24);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 8);
    } else if (mode == 1) {
        t = 2 * rnd.next(1, 12);
    } else if (mode == 2) {
        t = 2 * rnd.next(0, 12) + 1;
    } else if (mode == 3) {
        t = rnd.next(20, 200);
    } else {
        t = rnd.next(100000, 1000000);
    }

    vector<Road> roads;
    roads.reserve(m);

    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(1, 10);
        for (int i = 0; i < m; ++i) roads.push_back(makePairRoad(n));
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        m = rnd.next(1, 14);
        for (int i = 0; i < m; ++i) roads.push_back(makeTripleRoad(n));
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        m = rnd.next(4, 24);
        int duplicateAnchor = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            if (i % 4 == 0) {
                int b = rnd.next(1, n - 1);
                if (b >= duplicateAnchor) ++b;
                roads.push_back({1, duplicateAnchor, b, 0});
            } else if (rnd.next(2)) {
                roads.push_back(makePairRoad(n));
            } else {
                roads.push_back(makeTripleRoad(n));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        for (int i = 1; i < n; ++i) {
            roads.push_back({1, i, i + 1, 0});
        }
        int extra = rnd.next(1, 15);
        while (extra--) {
            roads.push_back(rnd.next(2) ? makePairRoad(n) : makeTripleRoad(n));
        }
        m = (int)roads.size();
    } else {
        n = rnd.next(6, 14);
        m = rnd.next(20, 60);
        for (int i = 0; i < m; ++i) {
            roads.push_back(rnd.next(100) < 35 ? makePairRoad(n) : makeTripleRoad(n));
        }
    }

    shuffle(roads.begin(), roads.end());

    println(n, (int)roads.size(), t);
    for (const Road& road : roads) {
        if (road.type == 1) {
            println(road.type, road.a, road.b);
        } else {
            println(road.type, road.a, road.b, road.c);
        }
    }

    return 0;
}

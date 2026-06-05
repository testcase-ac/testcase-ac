#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

vector<Edge> allEdges(int n, int m) {
    vector<Edge> edges;
    for (int player = 1; player <= n; ++player) {
        for (int pick = 1; pick <= m; ++pick) {
            edges.push_back({player, pick});
        }
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

vector<Edge> randomEdges(int n, int m, int count, bool allowDuplicates) {
    if (allowDuplicates) {
        vector<Edge> edges;
        for (int i = 0; i < count; ++i) {
            edges.push_back({rnd.next(1, n), rnd.next(1, m)});
        }
        return edges;
    }

    vector<Edge> pool = allEdges(n, m);
    pool.resize(count);
    return pool;
}

vector<Edge> concentratedEdges(int n, int m, int count, int playerLimit, int pickLimit) {
    vector<Edge> edges;
    playerLimit = min(playerLimit, n);
    pickLimit = min(pickLimit, m);
    for (int i = 0; i < count; ++i) {
        edges.push_back({rnd.next(1, playerLimit), rnd.next(1, pickLimit)});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int maxDistinct = n * m;

    vector<Edge> team1;
    vector<Edge> team2;

    if (mode == 0) {
        int k1 = rnd.next(1, min(20, maxDistinct));
        int k2 = rnd.next(1, min(20, maxDistinct));
        team1 = randomEdges(n, m, k1, false);
        team2 = randomEdges(n, m, k2, false);
    } else if (mode == 1) {
        int shared = rnd.next(1, min(10, maxDistinct));
        team1 = randomEdges(n, m, shared, false);
        team2 = team1;
        int extra = rnd.next(0, min(8, maxDistinct));
        vector<Edge> more = randomEdges(n, m, max(1, extra), false);
        if (rnd.next(0, 1) == 0) {
            team1.insert(team1.end(), more.begin(), more.begin() + extra);
        } else {
            team2.insert(team2.end(), more.begin(), more.begin() + extra);
        }
    } else if (mode == 2) {
        int k1 = rnd.next(1, 60);
        int k2 = rnd.next(1, 60);
        team1 = randomEdges(n, m, k1, true);
        team2 = randomEdges(n, m, k2, true);
    } else if (mode == 3) {
        int k1 = rnd.next(1, 40);
        int k2 = rnd.next(1, 40);
        team1 = concentratedEdges(n, m, k1, rnd.next(1, min(n, 4)), rnd.next(1, min(m, 4)));
        team2 = concentratedEdges(n, m, k2, rnd.next(1, min(n, 4)), rnd.next(1, min(m, 4)));
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        int k1 = rnd.next(1, 30);
        int k2 = rnd.next(31, 90);
        if (rnd.next(0, 1) == 0) {
            swap(k1, k2);
        }
        team1 = randomEdges(n, m, k1, true);
        team2 = randomEdges(n, m, k2, true);
    } else {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
        int diagonal = min(n, m);
        for (int i = 1; i <= diagonal; ++i) {
            team1.push_back({i, i});
            team2.push_back({i, diagonal - i + 1});
        }
        int extra1 = rnd.next(0, 20);
        int extra2 = rnd.next(0, 20);
        vector<Edge> more1 = randomEdges(n, m, extra1 + 1, true);
        vector<Edge> more2 = randomEdges(n, m, extra2 + 1, true);
        team1.insert(team1.end(), more1.begin(), more1.begin() + extra1);
        team2.insert(team2.end(), more2.begin(), more2.begin() + extra2);
    }

    shuffle(team1.begin(), team1.end());
    shuffle(team2.begin(), team2.end());

    println(n, m, int(team1.size()), int(team2.size()));
    for (const Edge& edge : team1) {
        println(edge.first, edge.second);
    }
    for (const Edge& edge : team2) {
        println(edge.first, edge.second);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void maybeFlip(Edge& edge) {
    if (rnd.next(2) == 0) {
        swap(edge.first, edge.second);
    }
}

void addExtraEdges(vector<Edge>& schedule, const vector<Edge>& candidates, int extraCount) {
    for (int i = 0; i < extraCount; ++i) {
        Edge edge = rnd.any(candidates);
        maybeFlip(edge);
        schedule.push_back(edge);
    }
}

vector<Edge> allSimpleEdges(int n) {
    vector<Edge> edges;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            edges.push_back({a, b});
        }
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 3 ? 12 : 9);
    vector<Edge> schedule;
    vector<Edge> candidates = allSimpleEdges(n);

    if (mode == 0) {
        for (int v = 1; v < n; ++v) {
            schedule.push_back({v, v + 1});
        }
        addExtraEdges(schedule, schedule, rnd.next(0, n + 3));
    } else if (mode == 1) {
        for (int v = n - 1; v >= 1; --v) {
            schedule.push_back({v, v + 1});
            if (rnd.next(3) == 0) {
                schedule.push_back(rnd.any(candidates));
            }
        }
        addExtraEdges(schedule, candidates, rnd.next(0, n));
    } else if (mode == 2) {
        int center = rnd.next(2) == 0 ? 1 : n;
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                schedule.push_back({center, v});
            }
        }
        addExtraEdges(schedule, schedule, rnd.next(n / 2, 2 * n));
    } else if (mode == 3) {
        shuffle(candidates.begin(), candidates.end());
        set<int> connected;
        connected.insert(1);
        while ((int)connected.size() < n) {
            int from = rnd.any(vector<int>(connected.begin(), connected.end()));
            int to = rnd.next(1, n);
            while (connected.count(to)) {
                to = rnd.next(1, n);
            }
            connected.insert(to);
            schedule.push_back({from, to});
        }
        int target = rnd.next(n - 1, min<int>(candidates.size(), n * 3));
        for (const Edge& edge : candidates) {
            if ((int)schedule.size() >= target) {
                break;
            }
            schedule.push_back(edge);
        }
    } else {
        for (int v = 1; v < n; ++v) {
            schedule.push_back({v, v + 1});
            int repeats = rnd.next(0, 3);
            for (int r = 0; r < repeats; ++r) {
                schedule.push_back({v, v + 1});
            }
        }
        addExtraEdges(schedule, candidates, rnd.next(1, n + 5));
    }

    shuffle(schedule.begin(), schedule.end());
    for (Edge& edge : schedule) {
        maybeFlip(edge);
    }

    println(n, (int)schedule.size());
    for (const Edge& edge : schedule) {
        println(edge.first, edge.second);
    }

    return 0;
}

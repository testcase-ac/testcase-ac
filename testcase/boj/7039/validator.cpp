#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
    multiset<pair<int, int>>::iterator activeIt;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25000, "N");
    inf.readEoln();

    vector<Rect> rects(n);
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(0, 1000000, "A");
        inf.readSpace();
        int b = inf.readInt(0, 1000000, "B");
        inf.readSpace();
        int c = inf.readInt(0, 1000000, "C");
        inf.readSpace();
        int d = inf.readInt(0, 1000000, "D");
        inf.readEoln();

        ensuref(a < c, "barn %d must have A < C, got A=%d C=%d", i + 1, a, c);
        ensuref(b < d, "barn %d must have B < D, got B=%d D=%d", i + 1, b, d);
        rects[i] = {a, b, c, d, {}};
    }
    inf.readEof();

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        return tie(rects[lhs].x1, rects[lhs].x2, rects[lhs].y1, rects[lhs].y2) <
               tie(rects[rhs].x1, rects[rhs].x2, rects[rhs].y1, rects[rhs].y2);
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> byRightEdge;
    multiset<pair<int, int>> activeY;

    for (int id : order) {
        const Rect& cur = rects[id];
        while (!byRightEdge.empty() && byRightEdge.top().first <= cur.x1) {
            int oldId = byRightEdge.top().second;
            byRightEdge.pop();
            activeY.erase(rects[oldId].activeIt);
        }

        auto next = activeY.lower_bound({cur.y1, -1});
        if (next != activeY.end()) {
            ensuref(next->first >= cur.y2,
                    "barn %d overlaps an earlier barn in both x and y ranges", id + 1);
        }
        if (next != activeY.begin()) {
            auto prev = next;
            --prev;
            ensuref(prev->second <= cur.y1,
                    "barn %d overlaps an earlier barn in both x and y ranges", id + 1);
        }

        rects[id].activeIt = activeY.insert({cur.y1, cur.y2});
        byRightEdge.push({cur.x2, id});
    }
}

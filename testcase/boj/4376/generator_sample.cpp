#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

Point freshPoint(set<pair<int, int>>& used, int limit) {
    while (true) {
        Point p{rnd.next(-limit, limit), rnd.next(-limit, limit)};
        if (used.insert({p.x, p.y}).second) return p;
    }
}

void printPoint(const Point& p) {
    println(p.x, p.y);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 6);
    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, 8);
        int m = rnd.next(1, 8);
        int s = rnd.next(1, 12);
        int v = rnd.next(1, 12);
        int reach = s * v;
        int limit = rnd.next(8, 40);

        set<pair<int, int>> used;
        vector<Point> gophers;
        vector<Point> holes;

        for (int i = 0; i < n; ++i) {
            gophers.push_back(freshPoint(used, limit));
        }

        if (mode == 0) {
            // Mostly reachable: holes are near randomly chosen gophers.
            for (int i = 0; i < m; ++i) {
                Point base = rnd.any(gophers);
                for (int tries = 0; tries < 200; ++tries) {
                    int dx = rnd.next(-min(reach, 8), min(reach, 8));
                    int dy = rnd.next(-min(reach, 8), min(reach, 8));
                    if (dx * dx + dy * dy > reach * reach) continue;
                    Point p{base.x + dx, base.y + dy};
                    if (used.insert({p.x, p.y}).second) {
                        holes.push_back(p);
                        break;
                    }
                }
                if ((int)holes.size() <= i) holes.push_back(freshPoint(used, limit));
            }
        } else if (mode == 1) {
            // Mostly unreachable: holes are shifted away from the gopher cluster.
            for (int i = 0; i < m; ++i) {
                Point p;
                do {
                    p = freshPoint(used, limit);
                    used.erase({p.x, p.y});
                    p.x += reach + rnd.next(2, 15);
                    p.y += reach + rnd.next(2, 15);
                } while (!used.insert({p.x, p.y}).second);
                holes.push_back(p);
            }
        } else if (mode == 2) {
            // Tight boundary cases around the exact reachable distance.
            for (int i = 0; i < m; ++i) {
                Point base = rnd.any(gophers);
                int sign = rnd.next(0, 1) ? 1 : -1;
                int offset = rnd.next(-1, 1);
                Point p{base.x + sign * max(1, reach + offset), base.y};
                if (!used.insert({p.x, p.y}).second) p = freshPoint(used, limit);
                holes.push_back(p);
            }
        } else {
            // Mixed random geometry with varied sizes and labels.
            for (int i = 0; i < m; ++i) {
                holes.push_back(freshPoint(used, limit));
            }
        }

        println(n, m, s, v);
        for (const Point& p : gophers) printPoint(p);
        for (const Point& p : holes) printPoint(p);
    }

    return 0;
}

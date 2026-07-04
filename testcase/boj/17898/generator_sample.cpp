#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Pylon {
    int x;
    int y;
    int a;
};

static void addPylon(vector<Pylon>& pylons, set<pair<int, int>>& used, int x, int y, int a) {
    if (x < 0 || x > 100000 || y < 0 || y > 100000) return;
    if (!used.insert({x, y}).second) return;
    pylons.push_back({x, y, a});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Pylon> pylons;
    set<pair<int, int>> used;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int n = rnd.next(1, 8);
        int baseX = rnd.next(0, 99980);
        int baseY = rnd.next(0, 99980);
        for (int i = 0; i < n; ++i) {
            addPylon(pylons, used, baseX + rnd.next(0, 20), baseY + rnd.next(0, 20), rnd.next(1, 2));
        }
    } else if (mode == 1) {
        int rows = rnd.next(2, 5);
        int width = rnd.next(3, 14);
        int baseX = rnd.next(0, 100000 - width - 2);
        int baseY = rnd.next(0, 100000 - rows);
        for (int y = 0; y < rows; ++y) {
            int cnt = rnd.next(1, width);
            vector<int> xs;
            for (int x = 0; x <= width; ++x) xs.push_back(baseX + x);
            shuffle(xs.begin(), xs.end());
            for (int i = 0; i < cnt; ++i) addPylon(pylons, used, xs[i], baseY + y, rnd.next(1, 2));
        }
    } else if (mode == 2) {
        int len = rnd.next(2, 18);
        int baseX = rnd.next(0, 100000 - 2 * len - 2);
        int baseY = rnd.next(0, 100000 - len - 1);
        for (int i = 0; i < len; ++i) {
            addPylon(pylons, used, baseX + i, baseY + i, rnd.next(1, 2));
            if (rnd.next(0, 1)) addPylon(pylons, used, baseX + 2 * len - i, baseY + i, rnd.next(1, 2));
        }
    } else if (mode == 3) {
        int rows = rnd.next(2, 6);
        int perRow = rnd.next(2, 10);
        int baseY = rnd.next(0, 100000 - rows);
        for (int y = 0; y < rows; ++y) {
            for (int i = 0; i < perRow; ++i) {
                int x = rnd.next(0, 100000);
                addPylon(pylons, used, x, baseY + y, rnd.next(1, 2));
            }
        }
    } else {
        vector<int> ys = {0, 1, 99999, 100000};
        vector<int> xs = {0, 1, 99999, 100000};
        shuffle(ys.begin(), ys.end());
        shuffle(xs.begin(), xs.end());
        int n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, 1) ? rnd.any(xs) : rnd.next(0, 100000);
            int y = rnd.next(0, 1) ? rnd.any(ys) : rnd.next(0, 100000);
            addPylon(pylons, used, x, y, rnd.next(1, 2));
        }
    }

    if (pylons.empty()) addPylon(pylons, used, 0, 0, 1);
    shuffle(pylons.begin(), pylons.end());

    println(static_cast<int>(pylons.size()));
    for (const Pylon& p : pylons) println(p.x, p.y, p.a);

    return 0;
}

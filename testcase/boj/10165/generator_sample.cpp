#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Route = pair<int, int>;

Route makeRoute(int n, int start, int length) {
    return {start, (start + length) % n};
}

void addRoute(vector<Route>& routes, set<Route>& used, int n, int start, int length) {
    length = max(1, min(length, n - 2));
    Route route = makeRoute(n, ((start % n) + n) % n, length);
    if (used.insert(route).second) routes.push_back(route);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 4) {
        n = rnd.next(100000000 - 1000, 1000000000);
    } else {
        n = rnd.next(3, 36);
    }

    int maxRoutes = min(30LL, 1LL * n * (n - 2));
    int targetM = rnd.next(2, maxRoutes);

    vector<Route> routes;
    set<Route> used;

    if (mode == 0) {
        int base = rnd.next(0, n - 1);
        int longLen = rnd.next(max(1, n / 3), n - 2);
        addRoute(routes, used, n, base, longLen);
        int innerCount = rnd.next(1, min(targetM - 1, max(1, longLen)));
        for (int i = 0; i < innerCount; ++i) {
            int offset = rnd.next(0, longLen - 1);
            int len = rnd.next(1, max(1, longLen - offset));
            addRoute(routes, used, n, base + offset, len);
        }
    } else if (mode == 1) {
        int base = rnd.next(max(1, n / 2), n - 1);
        int longLen = rnd.next(max(1, n / 3), n - 2);
        addRoute(routes, used, n, base, longLen);
        for (int i = 1; i < targetM; ++i) {
            int offset = rnd.next(0, longLen - 1);
            int len = rnd.next(1, max(1, longLen - offset));
            addRoute(routes, used, n, base + offset, len);
        }
    } else if (mode == 2) {
        int step = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < targetM; ++i) {
            int start = (i * step + rnd.next(0, step)) % n;
            int len = rnd.next(1, n - 2);
            addRoute(routes, used, n, start, len);
        }
    } else if (mode == 3) {
        vector<int> starts = {0, 1, n - 2, n - 1};
        for (int start : starts) {
            int len = rnd.next(1, n - 2);
            addRoute(routes, used, n, start, len);
        }
    } else {
        vector<int> starts = {0, 1, n / 2, n - 2, n - 1};
        vector<int> lens = {1, 2, n / 2, n - 3, n - 2};
        shuffle(starts.begin(), starts.end());
        shuffle(lens.begin(), lens.end());
        for (int start : starts)
            for (int len : lens)
                if ((int)routes.size() < targetM) addRoute(routes, used, n, start, len);
    }

    while ((int)routes.size() < targetM) {
        int start = rnd.next(0, n - 1);
        int len = rnd.next(1, n - 2);
        addRoute(routes, used, n, start, len);
    }

    shuffle(routes.begin(), routes.end());

    println(n);
    println((int)routes.size());
    for (Route route : routes) println(route.first, route.second);

    return 0;
}

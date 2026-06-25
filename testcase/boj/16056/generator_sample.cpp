#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = 1;
    int n = 1;
    set<pair<int, int>> edges;

    if (mode == 0) {
        m = rnd.next(1, 4);
        n = rnd.next(1, 7);
        int maxK = m * n;
        int k = rnd.next(0, min(maxK, 8));
        vector<pair<int, int>> all;
        for (int x = 1; x <= m; ++x)
            for (int y = 1; y <= n; ++y)
                all.push_back({x, y});
        shuffle(all.begin(), all.end());
        for (int i = 0; i < k; ++i)
            edges.insert(all[i]);
    } else if (mode == 1) {
        m = rnd.next(2, 6);
        n = rnd.next(3, 10);
        int hot = rnd.next(1, m);
        int degree = rnd.next(1, n);
        vector<int> devices;
        for (int y = 1; y <= n; ++y)
            devices.push_back(y);
        shuffle(devices.begin(), devices.end());
        for (int i = 0; i < degree; ++i)
            edges.insert({hot, devices[i]});
        for (int x = 1; x <= m; ++x) {
            if (x != hot && rnd.next(0, 2) == 0)
                edges.insert({x, rnd.next(1, n)});
        }
    } else if (mode == 2) {
        m = rnd.next(3, 8);
        n = rnd.next(3, 12);
        int socketLimit = rnd.next(1, m);
        int deviceLimit = rnd.next(1, n);
        for (int x = 1; x <= socketLimit; ++x)
            for (int y = 1; y <= deviceLimit; ++y)
                if (rnd.next(0, 3) != 0)
                    edges.insert({x, y});
        if (edges.empty())
            edges.insert({rnd.next(1, socketLimit), rnd.next(1, deviceLimit)});
    } else if (mode == 3) {
        m = rnd.next(4, 10);
        n = rnd.next(4, 12);
        for (int x = 1; x <= m; ++x) {
            int center = rnd.next(1, n);
            edges.insert({x, center});
            if (center > 1 && rnd.next(0, 1))
                edges.insert({x, center - 1});
            if (center < n && rnd.next(0, 1))
                edges.insert({x, center + 1});
        }
    } else if (mode == 4) {
        m = rnd.next(1, 12);
        n = rnd.next(1, 12);
        for (int x = 1; x <= m; ++x)
            for (int y = 1; y <= n; ++y)
                edges.insert({x, y});
    } else {
        m = rnd.next(20, 60);
        n = rnd.next(20, 60);
        int k = rnd.next(1, min(120, m * n));
        while ((int)edges.size() < k)
            edges.insert({rnd.next(1, m), rnd.next(1, n)});
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(m, n, (int)output.size());
    for (const auto& edge : output)
        println(edge.first, edge.second);

    return 0;
}

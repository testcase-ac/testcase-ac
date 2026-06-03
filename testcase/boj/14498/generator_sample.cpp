#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    vector<tuple<int, int, int>> reqs;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        int k = rnd.next(1, 8);
        for (int i = 0; i < k; ++i) {
            reqs.emplace_back(rnd.next(1, n), rnd.next(1, m), rnd.next(0, 1));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
        int a = rnd.next(1, n);
        int b = rnd.next(1, m);
        int k = rnd.next(2, 12);
        for (int i = 0; i < k; ++i) {
            int c = (i < 2 ? i : rnd.next(0, 1));
            reqs.emplace_back(a, b, c);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 7);
        m = rnd.next(2, 7);
        int fixedColor = rnd.next(1, n);
        int fixedModel = rnd.next(1, m);
        for (int model = 1; model <= m; ++model) {
            if (rnd.next(0, 1)) reqs.emplace_back(fixedColor, model, 0);
        }
        for (int color = 1; color <= n; ++color) {
            if (rnd.next(0, 1)) reqs.emplace_back(color, fixedModel, 1);
        }
        if (reqs.empty()) reqs.emplace_back(fixedColor, fixedModel, rnd.next(0, 1));
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        double keep = rnd.next(0.25, 0.75);
        for (int color = 1; color <= n; ++color) {
            for (int model = 1; model <= m; ++model) {
                if (rnd.next() < keep) reqs.emplace_back(color, model, rnd.next(0, 1));
            }
        }
        if (reqs.empty()) reqs.emplace_back(rnd.next(1, n), rnd.next(1, m), rnd.next(0, 1));
    } else if (mode == 4) {
        n = rnd.next(80, 128);
        m = rnd.next(80, 128);
        int k = rnd.next(1, 20);
        for (int i = 0; i < k; ++i) {
            int color = (rnd.next(0, 3) == 0 ? rnd.next(max(1, n - 5), n) : rnd.next(1, min(n, 6)));
            int model = (rnd.next(0, 3) == 0 ? rnd.next(max(1, m - 5), m) : rnd.next(1, min(m, 6)));
            reqs.emplace_back(color, model, rnd.next(0, 1));
        }
    } else {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
        int colors = rnd.next(1, min(n, 4));
        int models = rnd.next(1, min(m, 4));
        int copies = rnd.next(1, 3);
        for (int color = 1; color <= colors; ++color) {
            for (int model = 1; model <= models; ++model) {
                for (int rep = 0; rep < copies; ++rep) {
                    reqs.emplace_back(color, model, rnd.next(0, 1));
                }
            }
        }
    }

    shuffle(reqs.begin(), reqs.end());
    if ((int)reqs.size() > 512) reqs.resize(512);

    println(n, m, (int)reqs.size());
    for (auto [color, model, choice] : reqs) {
        println(color, model, choice);
    }

    return 0;
}

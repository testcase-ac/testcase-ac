#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Model {
    int h;
    int t;
    int e1;
    int e2;
};

Model randomModel(int n, int maxCost) {
    int h = rnd.next(2, n);
    int e1 = rnd.next(1, h);
    int e2 = rnd.next(1, h - 1);
    if (e2 >= e1) ++e2;

    return {h, rnd.next(1, maxCost), e1, e2};
}

Model deltaModel(int n, int delta, int cost) {
    int h = rnd.next(abs(delta) + 1, n);
    int lo = max(1, 1 - delta);
    int hi = min(h, h - delta);
    int e1 = rnd.next(lo, hi);
    return {h, cost, e1, e1 + delta};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 2;
    int r = 1;
    int d = 2;
    vector<Model> models;

    if (mode == 0) {
        n = rnd.next(2, 4);
        r = rnd.next(1, n);
        d = rnd.next(1, n);
        int m = rnd.next(1, 4);
        for (int i = 0; i < m; ++i) {
            models.push_back(randomModel(n, 20));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        r = rnd.next(1, n);
        d = rnd.next(1, n);
        int step = rnd.next(1, min(3, n - 1));
        int m = rnd.next(2, 8);
        for (int i = 0; i < m; ++i) {
            int delta = rnd.any(vector<int>{-step, step});
            models.push_back(deltaModel(n, delta, rnd.next(1, 50)));
        }
    } else if (mode == 2) {
        n = rnd.next(6, 15);
        r = rnd.next(1, n / 2);
        d = rnd.next(n / 2 + 1, n);
        int pos = r;
        while (pos < d) {
            int delta = min(rnd.next(1, 3), d - pos);
            models.push_back(deltaModel(n, delta, rnd.next(1, 30)));
            pos += delta;
        }
        int extras = rnd.next(1, 5);
        for (int i = 0; i < extras; ++i) {
            models.push_back(randomModel(n, 80));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        r = rnd.next(1, n);
        d = rnd.next(1, n);
        int parity = rnd.next(0, 1);
        r = (r % 2 == parity) ? r : (r == n ? r - 1 : r + 1);
        d = (d % 2 == parity) ? d : (d == n ? d - 1 : d + 1);
        if (rnd.next(0, 1)) d = (d == n ? 1 : d + 1);
        int m = rnd.next(2, 7);
        for (int i = 0; i < m; ++i) {
            int delta = rnd.any(vector<int>{-2, 2});
            models.push_back(deltaModel(n, delta, rnd.next(1, 100)));
        }
    } else {
        n = rnd.next(8, 20);
        r = rnd.next(1, n);
        d = rnd.next(1, n);
        int m = rnd.next(8, 18);
        for (int i = 0; i < m; ++i) {
            if (i % 4 == 0) {
                int delta = rnd.next(1, min(5, n - 1));
                if (rnd.next(0, 1)) delta = -delta;
                models.push_back(deltaModel(n, delta, rnd.next(900000, 1000000)));
            } else {
                models.push_back(randomModel(n, 200));
            }
        }
    }

    shuffle(models.begin(), models.end());

    println(n);
    println(r, d);
    println(static_cast<int>(models.size()));
    for (const Model& model : models) {
        println(model.h, model.t, model.e1, model.e2);
    }

    return 0;
}

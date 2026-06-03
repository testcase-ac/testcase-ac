#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = rnd.next(1, 30);
    vector<pair<int, int>> queries;

    auto addQuery = [&](int l, int r) {
        l = max(l, 2);
        r = min(r, 500000);
        if (l >= r) {
            l = 499999;
            r = 500000;
        }
        queries.push_back({l, r});
    };

    if (mode == 0) {
        for (int i = 0; i < q; ++i) {
            int l = rnd.next(2, 120);
            int r = rnd.next(l + 1, min(500000, l + rnd.next(1, 80)));
            addQuery(l, r);
        }
    } else if (mode == 1) {
        int center = rnd.next(2, 499950);
        for (int i = 0; i < q; ++i) {
            int span = rnd.next(1, 60);
            int shift = rnd.next(-50, 50);
            addQuery(center + shift, center + shift + span);
        }
    } else if (mode == 2) {
        for (int i = 0; i < q; ++i) {
            int l = rnd.next(2, 499999);
            int r = rnd.next(l + 1, 500000);
            if (rnd.next(0, 2) == 0) r = min(500000, l + rnd.next(1, 500));
            addQuery(l, r);
        }
    } else if (mode == 3) {
        vector<int> anchors = {2, 3, 4, 6, 7, 10, 15, 21, 499900, 499950, 499999};
        shuffle(anchors.begin(), anchors.end());
        for (int i = 0; i < q; ++i) {
            int l = anchors[i % (int)anchors.size()] + rnd.next(-3, 3);
            int r = l + rnd.next(1, 90);
            if (rnd.next(0, 4) == 0) r = 500000;
            addQuery(l, r);
        }
    } else {
        for (int i = 0; i < q; ++i) {
            int l = rnd.next(2, 499999);
            int width = rnd.wnext(500000 - l, -3) + 1;
            addQuery(l, l + width);
        }
    }

    println((int)queries.size());
    for (auto [l, r] : queries) println(l, r);

    return 0;
}

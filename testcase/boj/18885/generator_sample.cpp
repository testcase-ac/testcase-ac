#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    int valueMax = rnd.next(0, 5) == 0 ? 1000000 : rnd.next(3, 100);

    vector<vector<int>> seqs;
    seqs.reserve(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 5);
        int l = rnd.next(1, 8);
        vector<int> s;

        if (mode == 0) {
            s.push_back(rnd.next(0, valueMax));
        } else if (mode == 1) {
            int cur = rnd.next(0, valueMax);
            for (int j = 0; j < l; ++j) {
                s.push_back(cur);
                if (cur > 0) cur -= rnd.next(0, min(cur, max(1, valueMax / 4)));
            }
        } else if (mode == 2) {
            int lo = rnd.next(0, valueMax);
            int hi = rnd.next(lo, valueMax);
            s.assign(l, lo);
            if (l == 1) {
                s[0] = hi;
            } else {
                int pos = rnd.next(1, l - 1);
                s[pos] = hi;
            }
        } else if (mode == 3) {
            int a = rnd.next(0, valueMax);
            int b = rnd.next(0, valueMax);
            for (int j = 0; j < l; ++j) s.push_back(rnd.next(0, 1) ? a : b);
        } else if (mode == 4) {
            for (int j = 0; j < l; ++j) {
                s.push_back(rnd.next(0, 1) ? 0 : valueMax);
            }
        } else {
            int lo = rnd.next(0, valueMax);
            int hi = rnd.next(lo, valueMax);
            for (int j = 0; j < l; ++j) s.push_back(rnd.next(lo, hi));
        }

        seqs.push_back(s);
    }

    println(n);
    for (const auto& s : seqs) {
        printf("%d", static_cast<int>(s.size()));
        for (int x : s) printf(" %d", x);
        printf("\n");
    }

    return 0;
}

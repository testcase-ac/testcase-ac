#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int mode = rnd.next(0, 4);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 1) {
        int shift = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 2) {
        reverse(a.begin(), a.end());
    } else if (mode == 3) {
        int blockSize = rnd.next(1, min(n, 6));
        vector<vector<int>> blocks;
        for (int i = 0; i < n; i += blockSize) {
            vector<int> block;
            for (int j = i; j < min(n, i + blockSize); ++j) {
                block.push_back(a[j]);
            }
            if (rnd.next(0, 1)) {
                reverse(block.begin(), block.end());
            }
            blocks.push_back(block);
        }
        shuffle(blocks.begin(), blocks.end());
        a.clear();
        for (const auto& block : blocks) {
            a.insert(a.end(), block.begin(), block.end());
        }
    } else if (mode == 4) {
        shuffle(a.begin(), a.end());
    }

    int offset = rnd.next(0, 200000 - n);
    for (int& x : a) {
        x += offset;
    }

    int q = rnd.next(1, 25);
    vector<pair<int, int>> queries;
    queries.reserve(q);

    queries.push_back({rnd.next(1, n), rnd.next(1, n)});
    if (queries.back().first > queries.back().second) {
        swap(queries.back().first, queries.back().second);
    }
    if (n > 1 && static_cast<int>(queries.size()) < q) {
        queries.push_back({1, n});
    }

    while (static_cast<int>(queries.size()) < q) {
        int l;
        int r;
        int queryMode = rnd.next(0, 3);
        if (queryMode == 0) {
            l = rnd.next(1, n);
            r = l;
        } else if (queryMode == 1) {
            int len = rnd.next(1, min(n, 8));
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else if (queryMode == 2) {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        } else {
            l = 1;
            r = rnd.next(1, n);
        }
        queries.push_back({l, r});
    }

    println(n);
    println(a);
    println(q);
    for (auto [l, r] : queries) {
        println(l, r);
    }

    return 0;
}

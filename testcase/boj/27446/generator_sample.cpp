#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> pages;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int m = rnd.next(1, 25);
        int favorite = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 99) < 75) {
                pages.push_back(favorite);
            } else {
                pages.push_back(rnd.next(1, n));
            }
        }
    } else if (mode == 1) {
        n = rnd.next(8, 30);
        int keep = rnd.next(1, min(n, 8));
        set<int> seen;
        while ((int)seen.size() < keep) {
            seen.insert(rnd.next(1, n));
        }
        pages.assign(seen.begin(), seen.end());
    } else if (mode == 2) {
        n = rnd.next(10, 35);
        int l = rnd.next(1, n);
        int r = rnd.next(l, min(n, l + rnd.next(0, 8)));
        for (int page = 1; page <= n; ++page) {
            if (page < l || page > r) {
                pages.push_back(page);
                if (rnd.next(0, 99) < 25) {
                    pages.push_back(page);
                }
            }
        }
        if (pages.empty()) {
            pages.push_back(rnd.next(1, n));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 28);
        int parity = rnd.next(0, 1);
        for (int page = 1; page <= n; ++page) {
            if (page % 2 == parity) {
                pages.push_back(page);
            }
        }
        if (pages.empty()) {
            pages.push_back(1);
        }
    } else if (mode == 4) {
        n = rnd.next(1, 24);
        for (int page = 1; page <= n; ++page) {
            pages.push_back(page);
            if (rnd.next(0, 99) < 20) {
                pages.push_back(page);
            }
        }
    } else {
        n = rnd.next(20, 100);
        int m = rnd.next(30, 100);
        int blockStart = rnd.next(1, n);
        int blockEnd = rnd.next(blockStart, min(n, blockStart + rnd.next(0, 15)));
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 99) < 65) {
                pages.push_back(rnd.next(blockStart, blockEnd));
            } else {
                pages.push_back(rnd.next(1, n));
            }
        }
    }

    shuffle(pages.begin(), pages.end());
    if ((int)pages.size() > 100) {
        pages.resize(100);
    }

    println(n, (int)pages.size());
    println(pages);

    return 0;
}

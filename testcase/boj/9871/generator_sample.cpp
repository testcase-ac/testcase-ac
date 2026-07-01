#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 40);
    int m = rnd.next(2, min(n, 15));
    int q = rnd.next(1, min(n, 20));

    vector<int> p(m);
    for (int i = 0; i < m; ++i) {
        p[i] = i + 1;
    }

    if (mode == 0) {
        // Identity shuffle with varied query positions.
    } else if (mode == 1) {
        int shift = rnd.next(1, m - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
    } else if (mode == 2) {
        reverse(p.begin(), p.end());
    } else if (mode == 3) {
        for (int i = 0; i + 1 < m; i += 2) {
            swap(p[i], p[i + 1]);
        }
    } else if (mode == 4) {
        int block = rnd.next(2, min(m, 5));
        for (int start = 0; start < m; start += block) {
            int finish = min(m, start + block);
            rotate(p.begin() + start, p.begin() + start + 1, p.begin() + finish);
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    vector<int> queries;
    queries.push_back(1);
    if (q >= 2) {
        queries.push_back(n);
    }
    while ((int)queries.size() < q) {
        int queryMode = rnd.next(4);
        if (queryMode == 0) {
            queries.push_back(rnd.next(1, min(n, m + 2)));
        } else if (queryMode == 1) {
            queries.push_back(rnd.next(max(1, n - m - 2), n));
        } else {
            queries.push_back(rnd.next(1, n));
        }
    }
    shuffle(queries.begin(), queries.end());

    println(n, m, q);
    for (int x : p) {
        println(x);
    }
    for (int x : queries) {
        println(x);
    }

    return 0;
}

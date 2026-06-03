#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 16);
    } else {
        n = rnd.next(20, 45);
    }

    int m;
    if (n == 1) {
        m = 1;
    } else if (mode == 3) {
        m = n;
    } else {
        m = rnd.next(1, n);
    }

    vector<int> cuts;
    for (int i = 2; i <= n; ++i) {
        cuts.push_back(i);
    }
    shuffle(cuts.begin(), cuts.end());
    cuts.resize(m - 1);
    sort(cuts.begin(), cuts.end());

    vector<int> starts;
    starts.push_back(1);
    for (int cut : cuts) {
        starts.push_back(cut);
    }

    vector<int> ends(m);
    for (int i = 0; i + 1 < m; ++i) {
        ends[i] = starts[i + 1] - 1;
    }
    ends.back() = n;

    println(n, m);
    for (int i = 0; i < m; ++i) {
        int c;
        if (rnd.next(0, 4) == 0) {
            c = rnd.any(vector<int>{0, 1, 100000});
        } else {
            c = rnd.next(0, 100000);
        }
        println(starts[i], ends[i], c);
    }

    int q = rnd.next(3, mode == 3 ? 25 : 16);
    for (int i = 0; i < q; ++i) {
        int op = rnd.next(1, 2);
        int start_region = rnd.next(0, m - 1);
        int end_region = rnd.next(0, m - 1);

        bool wraps = false;
        if (m > 1 && rnd.next(0, 3) == 0) {
            start_region = rnd.next(1, m - 1);
            end_region = rnd.next(0, start_region - 1);
            wraps = true;
        } else if (start_region > end_region) {
            swap(start_region, end_region);
        }

        int x = rnd.next(starts[start_region], ends[start_region]);
        int y = rnd.next(starts[end_region], ends[end_region]);
        if (!wraps && start_region == end_region && x > y) {
            swap(x, y);
        }

        if (op == 1) {
            println(op, x, y);
        } else {
            int z = rnd.next(1, 1000000);
            println(op, x, y, z);
        }
    }
    println(0, 0, 0);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> catalan = {0, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796};

    int t = rnd.next(1, 20);
    println(t);

    for (int case_idx = 0; case_idx < t; ++case_idx) {
        int mode = rnd.next(0, 5);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(1, 4);
            k = rnd.next(1, min(100000, catalan[n] + 2));
        } else if (mode == 1) {
            n = rnd.next(5, 10);
            int delta = rnd.next(-2, 3);
            k = catalan[n] + delta;
            k = max(1, min(100000, k));
        } else if (mode == 2) {
            n = rnd.next(1, 10);
            k = rnd.next(catalan[n] + 1, 100000);
        } else if (mode == 3) {
            n = rnd.next(1, 10);
            k = rnd.next(1, catalan[n]);
        } else if (mode == 4) {
            n = rnd.any(vector<int>{1, 2, 9, 10});
            k = rnd.any(vector<int>{1, 2, 3, 99999, 100000});
        } else {
            n = rnd.next(1, 10);
            k = rnd.next(1, 100000);
        }

        println(n, k);
    }

    return 0;
}

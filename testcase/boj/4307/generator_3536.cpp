#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter for stick length
        int lmode = rnd.next(0, 2);
        int l;
        if (lmode == 0) l = rnd.next(1, 10);
        else if (lmode == 1) l = rnd.next(10, 100);
        else l = rnd.next(100, 1000);

        // Number of ants
        int n = rnd.next(1, 5);

        println(l, n);

        // Hyper-parameter for clustering of positions
        int cluster = rnd.next(0, 3);
        vector<int> pos;
        pos.reserve(n);
        for (int i = 0; i < n; ++i) {
            int p;
            if (cluster == 1) {
                // near left end
                p = rnd.next(0, l / 3);
            } else if (cluster == 2) {
                // near right end
                p = rnd.next((2 * l) / 3, l);
            } else if (cluster == 3) {
                // around center
                p = rnd.next(l / 3, (2 * l) / 3);
            } else {
                // uniform
                p = rnd.next(0, l);
            }
            pos.push_back(p);
        }

        shuffle(pos.begin(), pos.end());
        for (int p : pos) {
            println(p);
        }
    }

    return 0;
}

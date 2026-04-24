#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a hyper-parameter mode for diversity
    // 1: small jars [1,10]
    // 2: full range [1,100]
    // 3: one large jar [50,100], two small [1,10]
    // 4: all jars equal
    // 5: total is triangular number, split into three positive parts
    int mode = rnd.next(1, 5);
    int a, b, c;

    if (mode == 1) {
        a = rnd.next(1, 10);
        b = rnd.next(1, 10);
        c = rnd.next(1, 10);
    } else if (mode == 2) {
        a = rnd.next(1, 100);
        b = rnd.next(1, 100);
        c = rnd.next(1, 100);
    } else if (mode == 3) {
        int bigJar = rnd.next(1, 3);
        int big = rnd.next(50, 100);
        int s1 = rnd.next(1, 10);
        int s2 = rnd.next(1, 10);
        vector<int> v = {s1, s2};
        v.insert(v.begin() + (bigJar - 1), big);
        a = v[0];
        b = v[1];
        c = v[2];
    } else if (mode == 4) {
        int x = rnd.next(1, 100);
        a = b = c = x;
    } else {
        // Precompute triangular numbers >=3 up to sum<=300
        vector<int> T;
        for (int t = 2; t <= 24; t++) {
            int tri = t * (t + 1) / 2;
            if (tri <= 300) T.push_back(tri);
        }
        // Repeat until we get a valid split with each ≤100
        while (true) {
            int sum = rnd.any(T);
            // sum >= 3 here
            int u = rnd.next(1, sum - 2);
            int v = rnd.next(u + 1, sum - 1);
            int aa = u;
            int bb = v - u;
            int cc = sum - v;
            if (aa <= 100 && bb <= 100 && cc <= 100) {
                a = aa;
                b = bb;
                c = cc;
                break;
            }
        }
    }

    // Output the three jar sizes
    println(a, b, c);
    return 0;
}

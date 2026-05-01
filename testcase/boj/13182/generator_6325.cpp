#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(8, 12);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 4);
        int R, G, B, K;
        if (type == 0) {
            // small values
            R = rnd.next(1, 10);
            G = rnd.next(1, 10);
            B = rnd.next(1, 10);
            K = rnd.next(1, 10);
        } else if (type == 1) {
            // medium values
            R = rnd.next(1000, 1000000);
            G = rnd.next(1000, 1000000);
            B = rnd.next(1000, 1000000);
            K = rnd.next(1, 1000000);
        } else if (type == 2) {
            // large values
            R = rnd.next(100000000, 1000000000);
            G = rnd.next(100000000, 1000000000);
            B = rnd.next(100000000, 1000000000);
            K = rnd.next(1, 1000000000);
        } else if (type == 3) {
            // one of R, G, B is 1
            vector<int> v = { rnd.next(1, 1000000000), rnd.next(1, 1000000000), rnd.next(1, 1000000000) };
            int idx = rnd.next(0, 2);
            v[idx] = 1;
            R = v[0]; G = v[1]; B = v[2];
            K = rnd.next(1, 1000000000);
        } else {
            // small B, K > B
            B = rnd.next(1, 100);
            R = rnd.next(1, 100000);
            G = rnd.next(1, 100000);
            int maxK = min(1000000000, B * 100);
            K = rnd.next(B + 1, maxK);
        }
        println(R, G, B, K);
    }
    return 0;
}

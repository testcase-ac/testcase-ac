#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 10);
        int K;
        // push K to extremes sometimes
        if (rnd.next(1, 10) <= 2) {
            K = 1;
        } else if (rnd.next(1, 10) <= 2) {
            K = N;
        } else {
            K = rnd.next(1, N);
        }
        println(N, K);
        int type = rnd.next(0, 3);
        int zeroCat = -1;
        if (type == 2) {
            zeroCat = rnd.next(0, 4);
        }
        for (int i = 0; i < N; ++i) {
            vector<int> r(5);
            if (type == 0) {
                // full range
                for (int j = 0; j < 5; ++j)
                    r[j] = rnd.next(0, 10000);
            } else if (type == 1) {
                // small scores
                int mx = rnd.next(0, 20);
                for (int j = 0; j < 5; ++j)
                    r[j] = rnd.next(0, mx);
            } else if (type == 2) {
                // one category always zero
                for (int j = 0; j < 5; ++j) {
                    if (j == zeroCat) r[j] = 0;
                    else r[j] = rnd.next(0, 10000);
                }
            } else {
                // sparse zeros
                for (int j = 0; j < 5; ++j) {
                    if (rnd.next() < 0.3)
                        r[j] = 0;
                    else
                        r[j] = rnd.next(0, 10000);
                }
            }
            println(r);
        }
    }
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = rnd.next(2, 24);
    vector<int> a(N);

    if (mode == 0) {
        int x = rnd.next(0, N - 1);
        fill(a.begin(), a.end(), x);
    } else if (mode == 1) {
        for (int i = 0; i < N; ++i) a[i] = i;
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        int cap = rnd.next(0, min(N - 1, 5));
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, cap);
    } else if (mode == 3) {
        int split = rnd.next(1, N - 1);
        for (int i = 0; i < split; ++i) a[i] = rnd.next(0, min(N - 1, 3));
        for (int i = split; i < N; ++i) a[i] = rnd.next(max(0, N - 4), N - 1);
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        int missing = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            a[i] = rnd.next(0, N - 2);
            if (a[i] >= missing) ++a[i];
        }
    } else {
        int prefix = rnd.next(1, min(N, 8));
        for (int i = 0; i < N; ++i) {
            if (i < prefix) {
                a[i] = i;
            } else if (rnd.next(0, 2) == 0) {
                a[i] = rnd.next(0, prefix - 1);
            } else {
                a[i] = rnd.next(prefix - 1, N - 1);
            }
        }
        shuffle(a.begin(), a.end());
    }

    println(N);
    println(a);
    return 0;
}

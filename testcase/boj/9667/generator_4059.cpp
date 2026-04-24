#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small size
    int N = rnd.next(1, 10);
    // upper bound for parts
    int Amax = rnd.next(1, 20);
    // choose pattern for diversity
    int pattern = rnd.next(0, 4);

    vector<int> a(N+1);
    int maxStep = max(1, Amax / (N+1));

    if (pattern == 0) {
        // fully random
        for (int i = 0; i <= N; i++)
            a[i] = rnd.next(1, Amax);
    }
    else if (pattern == 1) {
        // increasing
        int curr = rnd.next(1, max(1, Amax/2));
        for (int i = 0; i <= N; i++) {
            int bound = Amax - curr;
            int inc = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr + inc;
            curr = a[i];
        }
    }
    else if (pattern == 2) {
        // decreasing
        int curr = rnd.next(max(1, Amax/2), Amax);
        for (int i = 0; i <= N; i++) {
            int bound = curr - 1;
            int dec = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr - dec;
            curr = a[i];
        }
    }
    else if (pattern == 3) {
        // mountain: up then down
        int peak = rnd.next(0, N);
        int curr = rnd.next(1, max(1, Amax/2));
        for (int i = 0; i <= peak; i++) {
            int bound = Amax - curr;
            int inc = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr + inc;
            curr = a[i];
        }
        for (int i = peak+1; i <= N; i++) {
            int bound = curr - 1;
            int dec = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr - dec;
            curr = a[i];
        }
    }
    else {
        // valley: down then up
        int valley = rnd.next(0, N);
        int curr = rnd.next(max(1, Amax/2), Amax);
        for (int i = 0; i <= valley; i++) {
            int bound = curr - 1;
            int dec = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr - dec;
            curr = a[i];
        }
        for (int i = valley+1; i <= N; i++) {
            int bound = Amax - curr;
            int inc = bound > 0 ? rnd.next(0, min(bound, maxStep)) : 0;
            a[i] = curr + inc;
            curr = a[i];
        }
    }

    // output
    println(N);
    for (int x : a) println(x);
    return 0;
}

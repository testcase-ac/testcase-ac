#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        vector<int> a(6);
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            int start = rnd.next(1, 100);
            int maxStep = (100 - start) / 5;
            int step = rnd.next(0, maxStep);
            for (int i = 0; i < 6; i++) a[i] = start + step * i;
        } else if (mode == 1) {
            int start = rnd.next(1, 100);
            int maxStep = (start - 1) / 5;
            int step = rnd.next(0, maxStep);
            for (int i = 0; i < 6; i++) a[i] = start - step * i;
        } else if (mode == 2) {
            for (int i = 0; i < 6; i++) a[i] = rnd.next(1, 20);
        } else if (mode == 3) {
            for (int i = 0; i < 6; i++) a[i] = rnd.next(80, 100);
        } else {
            int v = rnd.next(1, 100);
            for (int i = 0; i < 6; i++) a[i] = v;
        }
        if (mode >= 2) shuffle(a.begin(), a.end());
        bool eqCase = rnd.next(0, 9) == 0;
        long long N;
        if (eqCase) {
            N = accumulate(a.begin(), a.end(), 0LL);
        } else {
            int Nmode = rnd.next(0, 2);
            if (Nmode == 0) {
                N = rnd.next(1, 200);
            } else if (Nmode == 1) {
                N = rnd.next(201, 1000000);
            } else {
                N = rnd.next(1000001, 500000000);
            }
        }
        println(N);
        println(a);
    }
    return 0;
}

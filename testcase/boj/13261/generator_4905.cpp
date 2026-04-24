#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small L
    int L = rnd.next(1, 10);
    // Hyper-parameter for number of guards G
    double pg = rnd.next();
    int G;
    if (pg < 0.2) G = 1;
    else if (pg < 0.4) G = L;
    else G = rnd.next(1, L);

    // Hyper-parameter for C distribution: same, increasing, decreasing, random
    int mode = rnd.next(0, 3);
    vector<int> C(L);
    if (mode == 0) {
        int x = rnd.next(1, 100);
        for (int i = 0; i < L; i++) C[i] = x;
    } else {
        for (int i = 0; i < L; i++) {
            C[i] = rnd.next(1, 100);
        }
        if (mode == 1) {
            sort(C.begin(), C.end());
        } else if (mode == 2) {
            sort(C.rbegin(), C.rend());
        }
    }

    // Output
    println(L, G);
    println(C);

    return 0;
}

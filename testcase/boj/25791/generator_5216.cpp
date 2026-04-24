#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for number of lectures L
    const int Lmin = 1, Lmax = 20;
    vector<int> biases = {-1, 0, 1};
    int biasL = rnd.any(biases);
    int rangeL = Lmax - Lmin + 1;
    int L;
    if (biasL == 0) {
        L = rnd.next(Lmin, Lmax);
    } else {
        int wL = rnd.next(1, 2);
        int offsetL = rnd.wnext(rangeL, biasL * wL);
        L = Lmin + offsetL;
    }

    // Determine number of teachers T with bias toward small/large counts
    int T_min = (L + 2) / 3;
    int T_max = L;
    int T;
    if (T_min == T_max) {
        T = T_min;
    } else {
        int biasT = rnd.any(biases);
        int rangeT = T_max - T_min + 1;
        if (biasT == 0) {
            T = rnd.next(T_min, T_max);
        } else {
            int wT = rnd.next(1, 2);
            int offsetT = rnd.wnext(rangeT, biasT * wT);
            T = T_min + offsetT;
        }
    }

    // Output header
    println(L, T);

    // Generate teacher costs
    for (int i = 0; i < T; i++) {
        int style = rnd.next(0, 1);
        int a1, d12, d23;
        if (style == 0) {
            // small increments
            a1 = rnd.next(1, 20);
            d12 = rnd.next(1, 5);
            d23 = rnd.next(1, 5);
        } else {
            // larger increments
            a1 = rnd.next(10, 50);
            d12 = rnd.next(6, 20);
            d23 = rnd.next(6, 20);
        }
        int a2 = a1 + d12;
        int a3 = a2 + d23;
        println(a1, a2, a3);
    }

    return 0;
}

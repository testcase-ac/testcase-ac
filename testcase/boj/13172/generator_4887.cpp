#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of dice
    int M = rnd.next(1, 10);
    println(M);

    // Decide whether all N_i are the same
    bool sameN = rnd.next() < 0.2;

    // Generator for N_i
    auto genN = [&]() {
        double p = rnd.next();
        if (p < 0.3) {
            // trivial 1-faced die
            return 1;
        } else if (p < 0.6) {
            // small-sized die
            return rnd.next(2, 20);
        } else if (p < 0.8) {
            // medium-sized with bias toward large end
            return rnd.wnext(1000, 2) + 1;  // [1..1000], weighted high
        } else {
            // truly large Ni
            return rnd.next(100000000, 1000000000);
        }
    };

    // Generator for S_i
    auto genS = [&]() {
        double q = rnd.next();
        if (q < 0.5) {
            // small total
            return rnd.next(1, 100);
        } else if (q < 0.8) {
            // medium total, biased large
            return rnd.wnext(1000000, 2) + 1; // [1..1e6], weighted high
        } else {
            // large total
            return rnd.next(1, 1000000000);
        }
    };

    int baseN = sameN ? genN() : -1;
    for (int i = 0; i < M; i++) {
        int Ni = sameN ? baseN : genN();
        int Si = genS();
        println(Ni, Si);
    }

    return 0;
}

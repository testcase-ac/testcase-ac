#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N and Q
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);
    println(N, Q);

    // Hyper-parameters for flip patterns
    double pRepeat = rnd.next(0.0, 1.0);
    double pLocal  = rnd.next(0.0, 1.0);

    int last = -1;
    for (int i = 0; i < Q; i++) {
        int idx;
        if (last != -1 && rnd.next() < pRepeat) {
            // repeat the same position
            idx = last;
        } else if (last != -1 && rnd.next() < pLocal) {
            // flip a nearby position
            int shift = rnd.next(-2, 2);
            idx = last + shift;
            if (idx < 1) idx = 1;
            if (idx > N) idx = N;
        } else {
            // uniform random
            idx = rnd.next(1, N);
        }
        println(idx);
        last = idx;
    }
    return 0;
}

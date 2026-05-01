#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of counters
    int N = rnd.next(1, 20);
    // Processing times
    vector<long long> T(N);
    for (int i = 0; i < N; i++) {
        int tp = rnd.next(0, 2);
        if (tp == 0) {
            // small times
            T[i] = rnd.next(1, 10);
        } else if (tp == 1) {
            // moderate times
            T[i] = rnd.next(1, 1000);
        } else {
            // large times
            T[i] = rnd.next(1000000, 1000000000);
        }
    }
    // Number of people
    long long M;
    int tm = rnd.next(0, 2);
    if (tm == 0) {
        // small M, comparable to N
        M = rnd.next(1LL, (long long)N);
    } else if (tm == 1) {
        // medium M
        M = rnd.next(1LL, 100000LL);
    } else {
        // large M
        M = rnd.next(100000000LL, 1000000000LL);
    }
    // Output
    println(N, M);
    for (auto t : T) println(t);
    return 0;
}

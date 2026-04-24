#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the lock
    int N = rnd.next(1, 10);

    // Initial state
    string S;
    S.reserve(N);
    for (int i = 0; i < N; i++) {
        S.push_back(char('0' + rnd.next(0, 9)));
    }

    // Target state starts as S, then apply some group operations
    string T = S;

    int maxOps = max(1, N / 2);
    int numGroupOps = rnd.next(1, maxOps);
    for (int op = 0; op < numGroupOps; op++) {
        int segLen = rnd.next(1, min(3, N));
        int pos = rnd.next(0, N - segLen);
        int delta = rnd.next(1, 3) * (rnd.next(0, 1) ? 1 : -1);
        for (int j = pos; j < pos + segLen; j++) {
            int d = T[j] - '0';
            d = (d + delta % 10 + 10) % 10;
            T[j] = char('0' + d);
        }
    }

    // Random independent changes with probability pRandom
    double pRandom = rnd.next();
    for (int i = 0; i < N; i++) {
        if (rnd.next() < pRandom) {
            T[i] = char('0' + rnd.next(0, 9));
        }
    }

    // Output
    println(N);
    printf("%s\n", S.c_str());
    printf("%s\n", T.c_str());

    return 0;
}

#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(4, 8);
    println(T);
    for (int i = 0; i < T; i++) {
        int N = rnd.next(2, 30);
        int type;
        if (i == 0) type = 0;
        else if (i == 1) type = 1;
        else if (i == 2) type = 2;
        else type = rnd.next(3, 4);
        string S(N, '0');
        if (type == 0) {
            // all zeros
            S = string(N, '0');
        } else if (type == 1) {
            // all ones
            S = string(N, '1');
        } else if (type == 2) {
            // alternating starting with '0'
            for (int j = 0; j < N; j++) S[j] = (j % 2 == 0 ? '0' : '1');
        } else if (type == 3) {
            // alternating starting with '1'
            for (int j = 0; j < N; j++) S[j] = (j % 2 == 0 ? '1' : '0');
        } else {
            // mixed pattern: either blocks or random
            if (rnd.next(0, 1) == 0) {
                int B = rnd.next(1, min(5, N));
                int rem = N;
                int bit = rnd.next(0, 1);
                int idx = 0;
                for (int b = 0; b < B; b++) {
                    int maxLen = rem - (B - b - 1);
                    int len = rnd.next(1, maxLen);
                    for (int k = 0; k < len; k++) {
                        S[idx++] = char('0' + bit);
                    }
                    rem -= len;
                    bit ^= 1;
                }
            } else {
                // fully random
                for (int j = 0; j < N; j++) S[j] = char('0' + rnd.next(0, 1));
            }
        }
        println(N);
        println(S);
    }
    return 0;
}

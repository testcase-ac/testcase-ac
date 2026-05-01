#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 8);
    int N;
    string S;

    switch (mode) {
        case 1: {
            // Smallest length
            N = 1;
            S = string(1, char('0' + rnd.next(0, 1)));
            break;
        }
        case 2: {
            // All zeros
            N = rnd.next(1, 10);
            S = string(N, '0');
            break;
        }
        case 3: {
            // All ones
            N = rnd.next(1, 10);
            S = string(N, '1');
            break;
        }
        case 4: {
            // Single 1
            N = rnd.next(2, 10);
            S = string(N, '0');
            int pos = rnd.next(0, N - 1);
            S[pos] = '1';
            break;
        }
        case 5: {
            // Single 0
            N = rnd.next(2, 10);
            S = string(N, '1');
            int pos = rnd.next(0, N - 1);
            S[pos] = '0';
            break;
        }
        case 6: {
            // Alternating pattern
            N = rnd.next(2, 10);
            char start = rnd.next(0, 1) ? '0' : '1';
            S.resize(N);
            for (int i = 0; i < N; i++) {
                S[i] = (i % 2 == 0) ? start : (start == '0' ? '1' : '0');
            }
            break;
        }
        case 7: {
            // Balanced (about half ones)
            N = rnd.next(2, 10);
            int ones = N / 2 + rnd.next(0, N % 2); // either floor(N/2) or ceil(N/2)
            S = string(N, '0');
            vector<int> idx(N);
            for (int i = 0; i < N; i++) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < ones; i++) {
                S[idx[i]] = '1';
            }
            break;
        }
        case 8: {
            // Fully random
            N = rnd.next(1, 10);
            S.resize(N);
            for (int i = 0; i < N; i++) {
                S[i] = char('0' + rnd.next(0, 1));
            }
            break;
        }
    }

    println(N);
    println(S);

    return 0;
}

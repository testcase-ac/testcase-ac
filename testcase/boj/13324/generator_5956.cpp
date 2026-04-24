#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a random pattern type
    int type = rnd.next(0, 5);
    // N between 1 and 15, biased towards smaller for hand-checkability
    int N = rnd.wnext(15, -2) + 1;
    vector<int> A(N);
    switch (type) {
        case 0: {
            // Strictly increasing
            int cur = rnd.next(0, 10);
            for (int i = 0; i < N; i++) {
                cur += rnd.next(1, 5);
                A[i] = cur;
            }
            break;
        }
        case 1: {
            // Strictly decreasing
            vector<int> tmp(N);
            int cur = rnd.next(0, 10);
            for (int i = 0; i < N; i++) {
                tmp[i] = cur;
                cur += rnd.next(1, 5);
            }
            for (int i = 0; i < N; i++) {
                A[i] = tmp[N - 1 - i];
            }
            break;
        }
        case 2: {
            // All equal
            int val = rnd.next(0, 20);
            for (int &x : A) x = val;
            break;
        }
        case 3: {
            // Fully random in small range
            for (int &x : A) x = rnd.next(0, 20);
            break;
        }
        case 4: {
            // Few plateau segments with jumps
            int segments = rnd.next(1, min(N, 5));
            int rem = N, idx = 0;
            int cur = rnd.next(0, 10);
            for (int s = 0; s < segments; s++) {
                int len = (s + 1 == segments ? rem : rnd.next(1, rem - (segments - s - 1)));
                for (int j = 0; j < len; j++) {
                    A[idx++] = cur;
                }
                rem -= len;
                cur += rnd.next(1, 10);
            }
            break;
        }
        case 5: {
            // Mix of boundary values and random large
            int k = rnd.next(1, N);
            vector<int> idx(N);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; i++) {
                // assign either 0 or 2e9
                A[idx[i]] = rnd.next(0, 1) ? 0 : 2000000000;
            }
            for (int i = k; i < N; i++) {
                A[idx[i]] = rnd.next(0, 2000000000);
            }
            break;
        }
    }
    // Output
    println(N);
    println(A);
    return 0;
}

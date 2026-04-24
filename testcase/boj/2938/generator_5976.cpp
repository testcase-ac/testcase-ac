#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type to get both possible and impossible cases
    int type = rnd.next(0, 4);
    int N;
    vector<int> a;

    if (type == 0) {
        // Trivial N = 1, always possible
        N = 1;
        int cls = rnd.next(0, 2);
        if (cls == 0) a.push_back(3);
        else if (cls == 1) a.push_back(1);
        else a.push_back(2);
    }
    else if (type == 1) {
        // Only one non-zero class (1 or 2), always possible
        N = rnd.next(2, 10);
        int cls = rnd.any(vector<int>{1, 2});
        for (int i = 0; i < N; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + cls);
        }
    }
    else if (type == 2) {
        // Mix of 1s and 2s only, no zeros -> impossible (if N>=2)
        N = rnd.next(3, 10);
        int c1 = rnd.next(1, N-1);
        int c2 = N - c1;
        for (int i = 0; i < c1; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 1);
        }
        for (int i = 0; i < c2; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 2);
        }
    }
    else if (type == 3) {
        // Mix including zeros, always possible by using zeros as separators
        N = rnd.next(3, 10);
        int c0 = rnd.next(1, N - 2);
        int rem = N - c0;
        int c1 = rnd.next(0, rem);
        int c2 = rem - c1;
        for (int i = 0; i < c0; i++) {
            int m = rnd.next(1, 5);
            a.push_back(m * 3);
        }
        for (int i = 0; i < c1; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 1);
        }
        for (int i = 0; i < c2; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 2);
        }
    }
    else {
        // Fully random counts, may be possible or impossible
        N = rnd.next(1, 10);
        int c0 = rnd.next(0, N);
        int rem = N - c0;
        int c1 = rnd.next(0, rem);
        int c2 = rem - c1;
        for (int i = 0; i < c0; i++) {
            int m = rnd.next(1, 5);
            a.push_back(m * 3);
        }
        for (int i = 0; i < c1; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 1);
        }
        for (int i = 0; i < c2; i++) {
            int m = rnd.next(0, 9);
            a.push_back(m * 3 + 2);
        }
    }

    // Shuffle input order to avoid sorted patterns
    shuffle(a.begin(), a.end());

    // Output
    println(N);
    println(a);

    return 0;
}

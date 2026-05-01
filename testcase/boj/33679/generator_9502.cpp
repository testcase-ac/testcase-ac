#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<int> genIncreasing(int N) {
    vector<int> a(N);
    for (int i = 0; i < N; ++i) a[i] = i + 1;
    int maxFactor = max(1, 100000000 / max(1, N));
    int factor = rnd.next(1, maxFactor);
    if (rnd.next(0, 1)) {
        for (int i = 0; i < N; ++i) a[i] *= factor;
    }
    return a;
}

vector<int> genDecreasing(int N) {
    vector<int> a(N);
    for (int i = 0; i < N; ++i) a[i] = N - i;
    int maxFactor = max(1, 100000000 / max(1, N));
    int factor = rnd.next(1, maxFactor);
    if (rnd.next(0, 1)) {
        for (int i = 0; i < N; ++i) a[i] *= factor;
    }
    return a;
}

vector<int> genGenericArray(int N) {
    vector<int> a(N);
    int pattern = rnd.next(0, 8);

    switch (pattern) {
        case 0: { // strictly increasing small
            a = genIncreasing(N);
            break;
        }
        case 1: { // strictly decreasing small
            a = genDecreasing(N);
            break;
        }
        case 2: { // all equal
            int c;
            if (rnd.next(0, 4)) c = rnd.next(1, 10);
            else c = 100000000;
            for (int i = 0; i < N; ++i) a[i] = c;
            break;
        }
        case 3: { // random small with duplicates
            for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 7);
            break;
        }
        case 4: { // random full range
            for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 100000000);
            break;
        }
        case 5: { // mountain: increase then decrease
            int p = rnd.next(0, N - 1);
            for (int i = 0; i <= p; ++i) a[i] = i + 1;
            int val = p + 1;
            for (int i = p + 1; i < N; ++i) {
                val = max(1, val - 1);
                a[i] = val;
            }
            break;
        }
        case 6: { // valley: decrease then increase
            int p = rnd.next(0, N - 1);
            for (int i = 0; i <= p; ++i) a[i] = N - i;
            int val = max(1, N - p - 1);
            for (int i = p + 1; i < N; ++i) {
                val = val + 1;
                a[i] = val;
            }
            break;
        }
        case 7: { // random permutation of 1..N (scaled sometimes)
            for (int i = 0; i < N; ++i) a[i] = i + 1;
            shuffle(a.begin(), a.end());
            int maxFactor = max(1, 100000000 / max(1, N));
            if (rnd.next(0, 1)) {
                int factor = rnd.next(1, maxFactor);
                for (int i = 0; i < N; ++i) a[i] *= factor;
            }
            break;
        }
        case 8: { // few large, many small
            for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 5);
            int K = rnd.next(1, max(1, N / 2));
            vector<int> idx(N);
            for (int i = 0; i < N; ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < K; ++i) {
                a[idx[i]] = rnd.next(1000000, 100000000);
            }
            break;
        }
    }
    return a;
}

vector<int> rotateArray(const vector<int>& a, int shift) {
    int N = (int)a.size();
    vector<int> b(N);
    for (int i = 0; i < N; ++i)
        b[i] = a[(i + shift) % N];
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int mode = rnd.next(0, 7);
    switch (mode) {
        case 0: N = 1; break;
        case 1: N = 2; break;
        case 2: N = rnd.next(3, 5); break;
        case 3: N = rnd.next(6, 8); break;
        case 4: N = rnd.next(9, 12); break;
        case 5: N = rnd.next(13, 16); break;
        case 6: N = rnd.next(17, 20); break;
        case 7: N = rnd.next(3, 20); break;
        default: N = rnd.next(1, 20); break;
    }

    vector<int> A, B;
    int pairType = rnd.next(0, 5);

    if (pairType == 0) {
        // Independent arrays with generic patterns
        A = genGenericArray(N);
        B = genGenericArray(N);
    } else if (pairType == 1) {
        // Identical arrays
        A = genGenericArray(N);
        B = A;
    } else if (pairType == 2) {
        // Reverse arrays
        A = genGenericArray(N);
        B = A;
        reverse(B.begin(), B.end());
    } else if (pairType == 3) {
        // Rotated arrays
        A = genGenericArray(N);
        if (N == 1) {
            B = A;
        } else {
            int shift = rnd.next(1, N - 1);
            B = rotateArray(A, shift);
        }
    } else if (pairType == 4) {
        // One increasing, one decreasing
        if (rnd.next(0, 1)) {
            A = genIncreasing(N);
            B = genDecreasing(N);
        } else {
            A = genDecreasing(N);
            B = genIncreasing(N);
        }
    } else { // pairType == 5
        // One generic, other is rotation or reverse of it (mixed)
        A = genGenericArray(N);
        int sub = rnd.next(0, 2);
        if (sub == 0 || N == 1) {
            B = rotateArray(A, (N == 1 ? 0 : rnd.next(1, N - 1)));
        } else if (sub == 1) {
            B = A;
            reverse(B.begin(), B.end());
        } else {
            B = genGenericArray(N);
        }
    }

    println(N);
    println(A);
    println(B);

    return 0;
}

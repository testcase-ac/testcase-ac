#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> rotateVec(const vector<long long>& v, int shift) {
    int n = (int)v.size();
    vector<long long> res(n);
    for (int i = 0; i < n; ++i)
        res[i] = v[(i + shift) % n];
    return res;
}

bool isRotation(const vector<long long>& a, const vector<long long>& b) {
    int n = (int)a.size();
    if ((int)b.size() != n) return false;
    for (int s = 0; s < n; ++s) {
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (a[i] != b[(i + s) % n]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

long long randSmall() { // 1..9
    return 1 + rnd.next(9);
}

long long randMedium() { // 1..100
    return 1 + rnd.next(100);
}

long long randLarge() { // 1e9 .. 1e9+1000
    return 1000000000LL + rnd.next(1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 8);
    int N;
    vector<long long> A, B;

    switch (scenario) {
        case 0: { // very small YES (rotation or identical)
            N = rnd.next(1, 3);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = randSmall();
            int shift = (N == 1 ? 0 : rnd.next(0, N - 1));
            B = rotateVec(A, shift);
            break;
        }
        case 1: { // very small NO (change one element)
            N = rnd.next(1, 3);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = randSmall();
            B = A;
            int pos = rnd.next(0, N - 1);
            // ensure value different from A[pos]
            long long v = A[pos];
            long long nv;
            do {
                nv = 100 + rnd.next(50); // outside small domain 1..9
            } while (nv == v);
            B[pos] = nv;
            break;
        }
        case 2: { // small YES with periodic pattern and rotation
            N = rnd.next(4, 8);
            int k = rnd.next(2, min(4, N));
            vector<long long> pattern(k);
            for (int i = 0; i < k; ++i) pattern[i] = randSmall();
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = pattern[i % k];
            int shift = rnd.next(1, N - 1);
            B = rotateVec(A, shift);
            break;
        }
        case 3: { // medium NO, all distinct, same multiset but not rotation
            N = rnd.next(6, 15);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) {
                A[i] = 10LL * (i + 1); // distinct, simple pattern
            }
            B = A;
            reverse(B.begin(), B.end());
            if (isRotation(A, B)) {
                // break rotation if some very rare coincidence happens
                if (N >= 2) swap(B[0], B[1]);
            }
            break;
        }
        case 4: { // medium YES, identical arrays
            N = rnd.next(5, 15);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = randMedium();
            B = A;
            break;
        }
        case 5: { // medium NO, differ in exactly one element (new value)
            N = rnd.next(5, 15);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = randMedium();
            B = A;
            int pos = rnd.next(0, N - 1);
            // choose value outside 1..100 to guarantee it's new
            long long nv = 200 + rnd.next(100);
            B[pos] = nv;
            break;
        }
        case 6: { // predefined tricky NO sample
            N = 6;
            A = {1, 1, 2, 2, 3, 3};
            B = {1, 3, 3, 2, 2, 1};
            break;
        }
        case 7: { // all equal values, YES or NO
            N = rnd.next(2, 10);
            long long v1 = randSmall();
            bool yesCase = rnd.next(0, 1) == 1;
            A.assign(N, v1);
            if (yesCase) {
                B = A;
            } else {
                long long v2;
                do {
                    v2 = randSmall();
                } while (v2 == v1);
                B.assign(N, v2);
            }
            break;
        }
        case 8: { // larger values, moderate N, YES or NO
            N = rnd.next(5, 12);
            A.assign(N, 0);
            for (int i = 0; i < N; ++i) A[i] = randLarge();
            bool yesCase = rnd.next(0, 1) == 1;
            if (yesCase) {
                int shift = rnd.next(0, N - 1);
                B = rotateVec(A, shift);
            } else {
                B = A;
                int pos = rnd.next(0, N - 1);
                long long nv;
                do {
                    nv = randLarge() + 2000; // move outside the small large-domain slice we used
                } while (nv == B[pos]);
                B[pos] = nv;
            }
            break;
        }
    }

    println(N);
    println(A);
    println(B);

    return 0;
}

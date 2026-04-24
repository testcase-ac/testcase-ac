#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // pick n between 1 and 30, skewed towards small
    int n = rnd.wnext(29, 3) + 1;
    vector<int> f(n+1), s(n+1);
    // prepare lists of knights
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        A[i] = i+1;
        B[i] = n + i + 1;
    }
    int type = (n > 1 ? rnd.next(0, 4) : 0);
    if (type == 0) {
        // fully random
        for (int i = 1; i <= n; i++) {
            f[i] = rnd.next(n+1, 2*n);
        }
        for (int i = 1; i <= n; i++) {
            s[i] = rnd.next(1, n);
        }
    } else if (type == 1) {
        // perfect matching style
        shuffle(B.begin(), B.end());
        for (int i = 1; i <= n; i++) {
            f[i] = B[i-1];
        }
        shuffle(A.begin(), A.end());
        for (int i = 1; i <= n; i++) {
            s[i] = A[i-1];
        }
    } else if (type == 2) {
        // star-heavy
        int centerB = rnd.any(B);
        int centerA = rnd.any(A);
        for (int i = 1; i <= n; i++) {
            if (rnd.next(100) < 70) f[i] = centerB;
            else f[i] = rnd.any(B);
        }
        for (int i = 1; i <= n; i++) {
            if (rnd.next(100) < 70) s[i] = centerA;
            else s[i] = rnd.any(A);
        }
    } else if (type == 3) {
        // single big alternating cycle
        shuffle(A.begin(), A.end());
        shuffle(B.begin(), B.end());
        vector<int> order(2*n);
        bool startA = rnd.next(0,1) == 0;
        if (startA) {
            for (int i = 0; i < n; i++) {
                order[2*i]   = A[i];
                order[2*i+1] = B[i];
            }
        } else {
            for (int i = 0; i < n; i++) {
                order[2*i]   = B[i];
                order[2*i+1] = A[i];
            }
        }
        for (int i = 0; i < 2*n; i++) {
            int v = order[i];
            int w = order[(i+1)%(2*n)];
            if (v <= n) f[v] = w;
            else        s[v-n] = w;
        }
    } else {
        // type 4: multiple small cycles
        shuffle(A.begin(), A.end());
        shuffle(B.begin(), B.end());
        int k = rnd.next(1, n);
        vector<int> parts(k, 1);
        int rem = n - k;
        for (int i = 0; i < rem; i++) {
            parts[rnd.next(0, k-1)]++;
        }
        int curA = 0, curB = 0;
        for (int pc : parts) {
            vector<int> subA, subB;
            for (int i = 0; i < pc; i++) {
                subA.push_back(A[curA++]);
                subB.push_back(B[curB++]);
            }
            bool startA = rnd.next(0,1) == 0;
            int len = 2*pc;
            vector<int> cycle(len);
            for (int i = 0; i < len; i++) {
                if (startA) {
                    if (i % 2 == 0) cycle[i] = subA[i/2];
                    else            cycle[i] = subB[i/2];
                } else {
                    if (i % 2 == 0) cycle[i] = subB[i/2];
                    else            cycle[i] = subA[i/2];
                }
            }
            for (int i = 0; i < len; i++) {
                int v = cycle[i];
                int w = cycle[(i+1)%len];
                if (v <= n) f[v] = w;
                else        s[v-n] = w;
            }
        }
    }
    // output
    println(n);
    vector<int> vf(n), vs(n);
    for (int i = 1; i <= n; i++) vf[i-1] = f[i];
    for (int i = 1; i <= n; i++) vs[i-1] = s[i];
    println(vf);
    println(vs);
    return 0;
}

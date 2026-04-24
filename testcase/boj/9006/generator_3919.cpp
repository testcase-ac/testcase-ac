#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // sizes
        int n = rnd.next(1, 10);
        int m = rnd.next(1, 10);
        // mode: 0 => A < B, 1 => B < A, 2 => overlap
        int mode = rnd.next(0, 2);
        vector<int> A, B;
        if (mode == 0) {
            // A negative, B positive
            int a_hi = rnd.next(-20, -1);
            int a_lo = rnd.next(-100, a_hi - 1);
            if (a_hi - a_lo + 1 < n) a_lo = a_hi - n + 1;
            for (int x = a_lo; x <= a_hi; x++) A.push_back(x);
            shuffle(A.begin(), A.end());
            A.resize(n);
            int b_lo = rnd.next(1, 20);
            int b_hi = rnd.next(b_lo + m - 1, b_lo + 50);
            if (b_hi - b_lo + 1 < m) b_hi = b_lo + m - 1;
            for (int x = b_lo; x <= b_hi; x++) B.push_back(x);
            shuffle(B.begin(), B.end());
            B.resize(m);
        } else if (mode == 1) {
            // B negative, A positive
            int b_hi = rnd.next(-20, -1);
            int b_lo = rnd.next(-100, b_hi - 1);
            if (b_hi - b_lo + 1 < m) b_lo = b_hi - m + 1;
            for (int x = b_lo; x <= b_hi; x++) B.push_back(x);
            shuffle(B.begin(), B.end());
            B.resize(m);
            int a_lo = rnd.next(1, 20);
            int a_hi = rnd.next(a_lo + n - 1, a_lo + 50);
            if (a_hi - a_lo + 1 < n) a_hi = a_lo + n - 1;
            for (int x = a_lo; x <= a_hi; x++) A.push_back(x);
            shuffle(A.begin(), A.end());
            A.resize(n);
        } else {
            // overlapping range
            int mid = rnd.next(-30, 30);
            int span = rnd.next(n + m, max(n + m, 40));
            int lo = mid - rnd.next(0, span/2);
            int hi = lo + span;
            if (hi - lo + 1 < n + m) hi = lo + n + m - 1;
            vector<int> pool;
            for (int x = lo; x <= hi; x++) pool.push_back(x);
            shuffle(pool.begin(), pool.end());
            for (int i = 0; i < n; i++) A.push_back(pool[i]);
            for (int i = 0; i < m; i++) B.push_back(pool[n + i]);
        }
        // Shuffle final orders
        shuffle(A.begin(), A.end());
        shuffle(B.begin(), B.end());
        // Output this test case
        println(n, m);
        for (int x : A) println(x);
        for (int x : B) println(x);
    }
    return 0;
}

#include "testlib.h"
using namespace std;

int distinctInRange(int l, int r, const vector<int>& a) {
    set<int> s;
    for (int i = l; i <= r; i++) s.insert(a[i]);
    return (int)s.size();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (small for readability, but variable)
    int NType = rnd.next(0, 2);
    int N;
    if (NType == 0) N = rnd.next(2, 5);
    else if (NType == 1) N = rnd.next(6, 10);
    else N = rnd.next(11, 15);

    vector<int> a(N + 1);
    int arrPattern = rnd.next(0, 4);

    if (arrPattern == 0) {
        // All equal
        int val = rnd.next(1, 5);
        for (int i = 1; i <= N; i++) a[i] = val;
    } else if (arrPattern == 1) {
        // Strictly increasing
        for (int i = 1; i <= N; i++) a[i] = i;
    } else if (arrPattern == 2) {
        // Random from small set of values
        int K = rnd.next(2, min(5, N));
        vector<int> vals(K);
        for (int i = 0; i < K; i++) vals[i] = i + 1;
        for (int i = 1; i <= N; i++) a[i] = rnd.any(vals);
    } else if (arrPattern == 3) {
        // Periodic pattern
        int p = rnd.next(2, min(5, N));
        vector<int> base(p);
        for (int i = 0; i < p; i++) base[i] = i + 1;
        for (int i = 1; i <= N; i++) a[i] = base[(i - 1) % p];
    } else {
        // Segmented random: repeats plus some changes
        for (int i = 1; i <= N; i++) {
            if (i == 1 || rnd.next(0, 99) < 30)
                a[i] = rnd.next(1, 10);
            else
                a[i] = a[i - 1];
        }
    }

    int Qmax = min(25, N * 3);
    int Q = rnd.next(1, Qmax);

    vector<int> xs(Q + 1), rs(Q + 1), ls(Q + 1), ans(Q + 1);
    ans[0] = 0;

    for (int i = 1; i <= Q; i++) {
        int Q_prev = ans[i - 1];
        int l, r;

        if (i == 1) {
            // First query: ensure l1 <= N-1 so x1 <= N-1
            int l_hi = (N == 2 ? 1 : N - 1);
            l = rnd.next(1, l_hi);
            r = rnd.next(l, N);
        } else {
            int choice = rnd.next(0, 4);
            if (choice == 0) {
                l = rnd.next(1, N);
            } else if (choice == 1) {
                l = 1;
            } else if (choice == 2) {
                l = N;
            } else if (choice == 3) {
                if (Q_prev >= 2)
                    l = rnd.next(1, min(Q_prev - 1, N));
                else
                    l = rnd.next(1, N);
            } else {
                int base = Q_prev;
                if (base < 1) base = 1;
                if (base > N) base = N;
                int lo = max(1, base - 1);
                int hi = N;
                l = rnd.next(lo, hi);
            }

            int rChoice = rnd.next(0, 3);
            if (rChoice == 0) {
                r = rnd.next(l, N);
            } else if (rChoice == 1) {
                r = N;
            } else if (rChoice == 2) {
                r = l;
            } else {
                int maxLen = rnd.next(0, N - l);
                r = l + maxLen;
            }
        }

        ls[i] = l;
        rs[i] = r;
        ans[i] = distinctInRange(l, r, a);
        xs[i] = l - ans[i - 1];
    }

    // Output
    println(N);
    vector<int> outA(N);
    for (int i = 1; i <= N; i++) outA[i - 1] = a[i];
    println(outA);
    println(Q);
    for (int i = 1; i <= Q; i++) {
        println(xs[i], rs[i]);
    }

    return 0;
}

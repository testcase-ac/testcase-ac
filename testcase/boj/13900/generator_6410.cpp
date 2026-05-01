#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with a bias towards smaller sizes, but occasionally medium and larger for variability
    double p = rnd.next();
    int N;
    if (p < 0.7) {
        N = rnd.next(2, 10);
    } else if (p < 0.9) {
        N = rnd.next(11, 20);
    } else {
        N = rnd.next(21, 30);
    }

    vector<int> a(N);
    // Define several generation patterns to catch various edge cases
    // 1: Fully random in [0,10000]
    // 2: Zero-heavy (about half zeros)
    // 3: All equal
    // 4: Strictly increasing
    // 5: Strictly decreasing
    // 6: Few distinct values repeated
    int pattern = rnd.next(1, 6);

    if (pattern == 1) {
        // Fully random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(0, 10000);
    }
    else if (pattern == 2) {
        // Zero-heavy
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.5)
                a[i] = 0;
            else
                a[i] = rnd.next(1, 10000);
        }
    }
    else if (pattern == 3) {
        // All equal
        int v = rnd.next(0, 10000);
        for (int i = 0; i < N; i++)
            a[i] = v;
    }
    else if (pattern == 4 || pattern == 5) {
        // Generate N unique values then sort / reverse
        set<int> S;
        while ((int)S.size() < N)
            S.insert(rnd.next(0, 10000));
        vector<int> tmp(S.begin(), S.end());
        sort(tmp.begin(), tmp.end());
        if (pattern == 5)
            reverse(tmp.begin(), tmp.end());
        a = tmp;
    }
    else {
        // Few distinct values repeated
        int k = rnd.next(1, min(N, 5));
        set<int> S;
        while ((int)S.size() < k)
            S.insert(rnd.next(0, 10000));
        vector<int> vals(S.begin(), S.end());
        for (int i = 0; i < N; i++)
            a[i] = rnd.any(vals);
    }

    // Unless the pattern is strictly increasing/decreasing, shuffle to avoid accidental order
    if (pattern != 4 && pattern != 5)
        shuffle(a.begin(), a.end());

    // Output
    println(N);
    println(a);

    return 0;
}

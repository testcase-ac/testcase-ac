#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With some probability, emit one of the official examples (good for manual checking)
    if (rnd.next(0, 3) == 0) { // 1/4 chance approx (since 0..3 inclusive)
        int which = rnd.next(1, 5);
        if (which == 1) {
            // Example 1
            println(1);
            println(3);
            println(6);
        } else if (which == 2) {
            // Example 2
            println(3);
            vector<int> s = {5, 11, 18};
            println(s);
            println(9);
        } else if (which == 3) {
            // Example 3
            println(3);
            vector<int> s = {7, 13, 18};
            println(s);
            println(9);
        } else if (which == 4) {
            // Example 4
            println(5);
            vector<int> s = {1000, 1004, 4000, 4003, 5000};
            println(s);
            println(19);
        } else {
            // Example 5
            println(1);
            println(1000000000);
            println(8);
        }
        return 0;
    }

    // Random generation path
    const int Lmax = 10;
    const int maxN = 30;

    int L = rnd.next(1, Lmax);

    set<int> st;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Smallish numbers near 1..50
        while ((int)st.size() < L) {
            int x = rnd.next(1, 50);
            st.insert(x);
        }
    } else if (mode == 1) {
        // Random numbers in 1..200
        while ((int)st.size() < L) {
            int x = rnd.next(1, 200);
            st.insert(x);
        }
    } else if (mode == 2) {
        // Numbers clustered near 1e9
        const int MAXV = 1000000000;
        while ((int)st.size() < L) {
            int x = MAXV - rnd.next(0, 50);
            if (x >= 1)
                st.insert(x);
        }
    } else if (mode == 3) {
        // Widely spread random numbers in full range
        const int MAXV = 1000000000;
        while ((int)st.size() < L) {
            int x = rnd.next(1, MAXV);
            st.insert(x);
        }
    } else {
        // Contiguous block starting somewhere small
        int start = rnd.next(1, 1000);
        for (int i = 0; i < L; i++) {
            int x = start + i;
            if (x > 1000000000) break;
            st.insert(x);
        }
        // if fewer than L due to upper bound, fill randomly in [1,1e9]
        const int MAXV = 1000000000;
        while ((int)st.size() < L) {
            int x = rnd.next(1, MAXV);
            st.insert(x);
        }
    }

    // Occasionally force inclusion of 1 and/or 1e9 to stress boundary handling
    const int MAXV = 1000000000;
    bool mustInclude1 = (rnd.next(0, 3) == 0);
    bool mustIncludeMax = (rnd.next(0, 3) == 0);

    if (mustInclude1 && !st.count(1)) {
        if ((int)st.size() == L) {
            int idx = rnd.next(0, L - 1);
            auto it = st.begin();
            advance(it, idx);
            st.erase(it);
        }
        st.insert(1);
    }
    if (mustIncludeMax && !st.count(MAXV)) {
        if ((int)st.size() == L) {
            int idx = rnd.next(0, L - 1);
            auto it = st.begin();
            advance(it, idx);
            st.erase(it);
        }
        st.insert(MAXV);
    }

    // Convert to vector and shuffle for random ordering in input
    vector<int> S(st.begin(), st.end());
    shuffle(S.begin(), S.end());

    // Choose n with diverse sizes, but keep total output under ~500 chars
    int subtype = rnd.next(0, 2); // 0,1,2
    int lo, hi;
    if (subtype == 0) {
        lo = 1;
        hi = min(5, maxN);
    } else if (subtype == 1) {
        lo = max(1, L);
        hi = min(maxN, L + 10);
    } else {
        lo = max(1, L + 1);
        hi = maxN;
    }
    if (hi < lo) hi = lo; // safety, though ranges are constructed to avoid this
    int n = rnd.next(lo, hi);

    // Output
    println((int)S.size()); // L (may equal original L)
    println(S);
    println(n);

    return 0;
}

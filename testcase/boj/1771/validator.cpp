#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 500000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // Check permutation: all values 1..N appear exactly once
    vector<int> cnt(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        cnt[a[i]]++;
        ensuref(cnt[a[i]] == 1, "value %d appears more than once at position %d", a[i], i + 1);
    }
    for (int v = 1; v <= N; ++v) {
        ensuref(cnt[v] == 1, "value %d does not appear in the permutation", v);
    }

    // Problem states: "항상 가능한 경우만이 입력으로 주어지며"
    // We must verify that there exists a sequence of merges that reduces
    // N single-card bundles to one bundle, where every merged bundle is "valid":
    // its numbers are consecutive integers (in any order).
    //
    // Existence check: simulate merges using a stack of intervals [mn, mx].
    // Adjacent bundles A and B (with intervals [mn1, mx1], [mn2, mx2]) can be merged
    // iff mn = min(mn1, mn2), mx = max(mx1, mx2) satisfy mx - mn + 1 = size(A)+size(B).
    // Since initial bundles are singletons, and we maintain size = mx - mn + 1 for valid bundles,
    // this is equivalent to checking if after a linear greedy pass we end with a single bundle.

    struct Bundle {
        int mn, mx;
    };

    vector<Bundle> st;
    st.reserve(N);

    for (int i = 0; i < N; ++i) {
        int x = a[i];
        Bundle cur{ x, x };
        st.push_back(cur);

        // Try to greedily merge as much as possible with previous bundles
        while (st.size() >= 2) {
            Bundle b = st.back(); st.pop_back();
            Bundle aB = st.back(); st.pop_back();
            int mn = min(aB.mn, b.mn);
            int mx = max(aB.mx, b.mx);
            long long size = (long long)mx - mn + 1;
            long long totalCards = (long long)(aB.mx - aB.mn + 1) + (long long)(b.mx - b.mn + 1);
            if (size == totalCards) {
                // merged bundle still valid
                st.push_back({mn, mx});
            } else {
                // cannot merge; put them back as two separate bundles
                st.push_back(aB);
                st.push_back(b);
                break;
            }
        }
    }

    ensuref((int)st.size() == 1,
            "Permutation does not allow full merging into one valid bundle (remaining bundles: %d)",
            (int)st.size());

    inf.readEof();
}

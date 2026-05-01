#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases (lines before -1)
    int T = rnd.next(6, 10);
    set<long long> st;
    // Always include trivial edge cases
    st.insert(0);
    st.insert(1);
    // Some small n
    int small_cnt = rnd.next(1, 3);
    for (int i = 0; i < small_cnt && st.size() < (size_t)T; i++) {
        st.insert(rnd.next(2, 100));
    }
    // Include cases around the Pisano period for mod 10000 (period = 15000)
    const int P = 15000;
    long long nearMax1 = 1000000000LL - rnd.next(0, 100);
    vector<long long> edges = {P - 1, P, P + 1, 2LL * P, nearMax1, 1000000000LL};
    shuffle(edges.begin(), edges.end());
    int ec = rnd.next(2, 4), added = 0;
    for (long long x : edges) {
        if (added >= ec || st.size() >= (size_t)T) break;
        st.insert(x);
        added++;
    }
    // Fill the rest with random large values
    while (st.size() < (size_t)T) {
        st.insert(rnd.next(101, 1000000000));
    }
    // Shuffle the test cases for variety
    vector<long long> tests(st.begin(), st.end());
    shuffle(tests.begin(), tests.end());
    // Output each n, then -1
    for (long long x : tests) println(x);
    println(-1);
    return 0;
}

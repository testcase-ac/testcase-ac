#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: decide scenario for value ranges
    int scenario = rnd.next(0, 2);

    // Choose N and M
    int N = rnd.next(1, 8);
    int M = rnd.next(1, N);

    int minVal, maxVal;
    if (scenario == 0) {
        // Small values
        minVal = rnd.next(1, 5);
        maxVal = rnd.next(minVal + N - 1, minVal + 10);
    } else if (scenario == 1) {
        // Medium values
        minVal = rnd.next(50, 200);
        int hi = min(minVal + 1000, 10000);
        maxVal = rnd.next(minVal + N - 1, hi);
    } else {
        // Large values
        maxVal = rnd.next(2 * N, 10000);
        int maxOffset = maxVal - N + 1;
        int offset = rnd.next(N - 1, min(maxOffset, 1000));
        minVal = maxVal - offset;
    }

    // Generate N distinct numbers in [minVal, maxVal]
    set<int> st;
    while ((int)st.size() < N) {
        st.insert(rnd.next(minVal, maxVal));
    }
    vector<int> a(st.begin(), st.end());

    // Hyper-parameter: sometimes output sorted, sometimes random
    if (rnd.next(0, 1) == 0) {
        sort(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    // Output
    println(N, M);
    println(a);

    return 0;
}

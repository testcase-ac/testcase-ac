#include "testlib.h"
#include <vector>
#include <stack>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // Read heights
    vector<int> h = inf.readInts(N, 1, 100000, "height");
    inf.readEoln();

    // Check uniqueness
    set<int> seen;
    for (int i = 0; i < N; i++) {
        int v = h[i];
        ensuref(!seen.count(v),
                "Duplicate height %d at position %d", v, i+1);
        seen.insert(v);
    }

    // Compute next greater element to the right
    vector<int> nextGreater(N, N);
    stack<int> st;
    for (int i = 0; i < N; i++) {
        while (!st.empty() && h[i] > h[st.top()]) {
            nextGreater[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    // Compute maximum number of kills
    long long maxKills = 0;
    for (int i = 0; i < N; i++) {
        int j = nextGreater[i];
        long long kills = (long long)j - i - 1;
        ensuref(kills >= 0,
                "Computed negative kills for index %d: %lld", i+1, kills);
        if (kills > maxKills) maxKills = kills;
    }

    // maxKills cannot exceed N-1
    ensuref(maxKills <= N-1,
            "Maximum kills %lld exceeds N-1=%d", maxKills, N-1);

    inf.readEof();
    return 0;
}

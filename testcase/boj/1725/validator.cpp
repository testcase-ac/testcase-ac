#include "testlib.h"
#include <vector>
#include <stack>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of bars
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read heights
    vector<long long> h;
    h.reserve(N + 1);
    for (int i = 0; i < N; i++) {
        long long hi = inf.readLong(0LL, 1000000000LL, "h_i");
        inf.readEoln();
        h.push_back(hi);
    }
    // Append sentinel
    h.push_back(0LL);

    // Compute maximum rectangle area to validate the bound ≤ 2e9
    stack<int> st;
    long long maxArea = 0;
    for (int i = 0; i <= N; i++) {
        long long curH = h[i];
        while (!st.empty() && curH < h[st.top()]) {
            int tp = st.top();
            st.pop();
            int left = st.empty() ? 0 : st.top() + 1;
            int right = i - 1;
            int width = right - left + 1;
            __int128 area = (__int128)h[tp] * width;
            if (area > maxArea) {
                maxArea = (long long)area;
            }
        }
        st.push(i);
    }
    ensuref(maxArea <= 2000000000LL,
            "Maximum rectangle area %lld exceeds limit of 2000000000", maxArea);

    inf.readEof();
    return 0;
}

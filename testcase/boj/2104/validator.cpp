#include "testlib.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_A = 1000000;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<long long> A(N + 1);
    vector<long long> prefix(N + 1, 0);

    // Read array A[1..N]
    for (int i = 1; i <= N; ++i) {
        A[i] = inf.readInt(0, MAX_A, "A_i");
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // Compute prefix sums
    for (int i = 1; i <= N; ++i) {
        prefix[i] = prefix[i - 1] + A[i];
    }

    // Compute maximum score using monotonic stack
    // For each position as minimum, find maximal range where it's the minimum
    vector<int> L(N + 1), R(N + 1);

    // Previous smaller element (strictly smaller) to the left
    {
        stack<int> st;
        for (int i = 1; i <= N; ++i) {
            while (!st.empty() && A[st.top()] >= A[i]) st.pop();
            L[i] = st.empty() ? 1 : st.top() + 1;
            st.push(i);
        }
    }

    // Next smaller element (strictly smaller) to the right
    {
        stack<int> st;
        for (int i = N; i >= 1; --i) {
            while (!st.empty() && A[st.top()] > A[i]) st.pop();
            R[i] = st.empty() ? N : st.top() - 1;
            st.push(i);
        }
    }

    long long best = 0;
    for (int i = 1; i <= N; ++i) {
        if (A[i] == 0) continue; // contribution is zero anyway
        long long sum = prefix[R[i]] - prefix[L[i] - 1];
        long long score = sum * A[i];
        if (score > best) best = score;
    }

    // Ensure answer is non-negative and within safe bounds (using 64-bit is enough)
    ensuref(best >= 0, "Computed maximum score is negative, which should be impossible.");
    // Theoretical max: N * MAX_A * MAX_A <= 1e5 * 1e6 * 1e6 = 1e17 < 2^63
    ensuref(best <= (long long)4e18, "Computed maximum score too large: %lld", best);

    inf.readEof();
}

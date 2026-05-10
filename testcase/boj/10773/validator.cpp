#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of operations
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    vector<int> st;
    st.reserve(K);
    long long sum = 0;

    // Process each operation
    for (int i = 0; i < K; i++) {
        int x = inf.readInt(0, 1000000, "x");
        inf.readEoln();
        if (x == 0) {
            // Must have something to pop
            ensuref(!st.empty(),
                    "Operation %d is 0 but the stack is empty; cannot delete",
                    i + 1);
            int last = st.back();
            st.pop_back();
            sum -= last;
        } else {
            st.push_back(x);
            sum += x;
        }
    }

    // The problem guarantees that the final sum fits in 2^31-1
    ensuref(sum <= 2147483647LL,
            "Final sum %lld exceeds 2^31-1", sum);

    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int tc = 0; tc < P; tc++) {
        // Test case number T
        char buf[32];
        sprintf(buf, "T[%d]", tc+1);
        int T = inf.readInt(1, P, buf);

        // Read 20 heights, positive integers, distinct
        vector<int> h(20);
        // after T there must be a space before the first height
        inf.readSpace();
        for (int i = 0; i < 20; i++) {
            sprintf(buf, "h[%d][%d]", tc+1, i+1);
            h[i] = inf.readInt(1, 2147483647, buf);
            if (i + 1 < 20) inf.readSpace();
        }
        inf.readEoln();

        // Ensure heights are distinct
        {
            set<int> st;
            for (int i = 0; i < 20; i++) {
                bool inserted = st.insert(h[i]).second;
                ensuref(inserted,
                        "Duplicate height in test case %d: %d",
                        T, h[i]);
            }
        }
    }

    inf.readEof();
    return 0;
}

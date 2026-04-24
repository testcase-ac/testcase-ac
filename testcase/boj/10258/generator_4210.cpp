#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Length of the bitstring
        int N = rnd.next(2, 31);
        string s(N, '0');
        // Pattern type for diversity
        int type = rnd.next(0, 4);
        if (type == 0) {
            // Random density
            double p = rnd.next(0.0, 1.0);
            for (int i = 0; i < N; i++)
                if (rnd.next() < p) s[i] = '1';
        } else if (type == 1) {
            // All zeros or all ones
            char c = rnd.next(0,1) ? '1' : '0';
            for (int i = 0; i < N; i++) s[i] = c;
        } else if (type == 2) {
            // Alternating
            bool start1 = rnd.next(0,1);
            for (int i = 0; i < N; i++)
                s[i] = ((i % 2 == 0) ^ start1) ? '1' : '0';
        } else if (type == 3) {
            // Single one
            int pos = rnd.next(0, N-1);
            s[pos] = '1';
        } else {
            // Clustered ones
            int maxClusters = max(1, N/4);
            int C = rnd.next(1, maxClusters);
            for (int k = 0; k < C; k++) {
                int L = rnd.next(1, max(1, N/2));
                int start = rnd.next(0, N - L);
                for (int i = start; i < start + L; i++)
                    s[i] = '1';
            }
        }
        println(s);
    }
    return 0;
}

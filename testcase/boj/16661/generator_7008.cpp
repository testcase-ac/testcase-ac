#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide number of test cases (at most 15)
    int T = rnd.next(1, 15);
    // Total sum constraint for n+m
    int rem = 150;
    vector<int> ns(T), ms(T);
    for (int i = 0; i < T; i++) {
        // Ensure remaining tests can have at least size 2
        int min_rem = 2 * (T - 1 - i);
        int max_s = min(rem - min_rem, 30);
        if (max_s < 2) max_s = 2;
        int s = rnd.next(2, max_s);
        int n = rnd.next(1, s - 1);
        int m = s - n;
        ns[i] = n;
        ms[i] = m;
        rem -= s;
    }

    // Output number of test cases
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int n = ns[ti], m = ms[ti];
        // Choose a case type for diversity
        int type = rnd.next(0, 3);
        // Prepare adjacency matrix
        vector<string> mat(n, string(m, '0'));
        if (type == 0) {
            // Random density
            double density = rnd.next();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (rnd.next() < density)
                        mat[i][j] = '1';
        } else if (type == 1) {
            // Fully connected
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    mat[i][j] = '1';
        } else if (type == 2) {
            // No edges (all '0'): do nothing
        } else {
            // Structured sliding windows
            for (int i = 0; i < n; i++) {
                if (m >= 2) {
                    int w = rnd.next(2, m);
                    int start = rnd.next(0, m - w);
                    for (int j = start; j < start + w; j++)
                        mat[i][j] = '1';
                } else {
                    // single column
                    mat[i][0] = '1';
                }
            }
        }
        // Output this test
        println(n, m);
        for (int i = 0; i < n; i++) {
            printf("%s\n", mat[i].c_str());
        }
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Number of pieces
        int N = rnd.next(1, 10);
        // Hyper-parameter to skew total mismatches
        vector<int> skew_vals = { -2, -1, 0, 1, 2 };
        int t_mis = rnd.any(skew_vals);
        // M mismatches in total, from 0 to N
        int M = rnd.wnext(N + 1, t_mis);
        // Hyper-parameter to skew type distribution
        vector<int> skew_type = { -1, 0, 1 };
        int t_type = rnd.any(skew_type);
        // Number of WB mismatches
        int wb = rnd.wnext(M + 1, t_type);
        int bw = M - wb;

        // Prepare positions
        vector<int> pos(N);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());

        // Build initial and target strings
        string init(N, 'W'), target(N, 'W');
        // First wb positions: W -> B
        for (int i = 0; i < wb; i++) {
            int p = pos[i];
            init[p] = 'W';
            target[p] = 'B';
        }
        // Next bw positions: B -> W
        for (int i = wb; i < wb + bw; i++) {
            int p = pos[i];
            init[p] = 'B';
            target[p] = 'W';
        }
        // The rest: no mismatch
        for (int i = wb + bw; i < N; i++) {
            int p = pos[i];
            char c = rnd.any(vector<char>{'W', 'B'});
            init[p] = c;
            target[p] = c;
        }

        // Output the test case
        println(N);
        println(init);
        println(target);
    }
    return 0;
}

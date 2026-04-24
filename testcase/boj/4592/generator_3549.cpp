#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);

    for (int tc = 0; tc < T; ++tc) {
        // Length of this sequence
        int N = rnd.next(1, 25);
        vector<int> seq;
        seq.reserve(N);

        // Choose a generation mode for diversity
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // Pure random, low chance of incidental duplicates
            for (int i = 0; i < N; ++i) {
                seq.push_back(rnd.next(1, 99));
            }
        } else if (mode == 1) {
            // Clustered duplicates: split into a few runs
            int runs = rnd.next(1, min(N, 5));
            // Generate random run lengths summing to N
            vector<int> lens(runs, 1);
            int rem = N - runs;
            for (int i = 0; i < rem; ++i) {
                lens[rnd.next(0, runs - 1)]++;
            }
            // Build runs
            for (int r = 0; r < runs; ++r) {
                int val = rnd.next(1, 99);
                for (int i = 0; i < lens[r]; ++i) {
                    seq.push_back(val);
                }
            }
        } else {
            // Moderate duplicates: ~30% chance repeat previous
            for (int i = 0; i < N; ++i) {
                if (i > 0 && rnd.next(0, 9) < 3) {
                    seq.push_back(seq.back());
                } else {
                    seq.push_back(rnd.next(1, 99));
                }
            }
        }

        // Output this test case: N followed by the sequence
        vector<int> line;
        line.push_back(N);
        for (int x : seq) line.push_back(x);
        println(line);
    }

    // Terminate input
    println(0);

    return 0;
}

#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N
    int N = rnd.next(1, 10);
    // K in [0, min(N-1,5)], with weighted bias
    int maxK = min(N - 1, 5);
    int hiK = maxK + 1;  // rnd.wnext(hiK, t) gives [0..maxK]
    vector<int> Ts = {-2, -1, 0, 1, 2};
    int t = rnd.any(Ts);
    int K = rnd.wnext(hiK, t);

    // Choose pattern type for FJ's sequence
    int pattern = rnd.next(0, 2);
    vector<char> seq;
    if (pattern == 0) {
        // Fully random gestures
        for (int i = 0; i < N; i++)
            seq.push_back(rnd.any(string("HPS")));
    } else if (pattern == 1) {
        // Random runs of identical gestures
        int maxRuns = min(N, 5);
        int numRuns = rnd.next(1, maxRuns);
        int rem = N;
        vector<int> lengths;
        for (int i = 0; i < numRuns; i++) {
            if (i == numRuns - 1) {
                lengths.push_back(rem);
            } else {
                int l = rnd.next(1, rem - (numRuns - i - 1));
                lengths.push_back(l);
                rem -= l;
            }
        }
        char prev = 0;
        for (int len : lengths) {
            string choices = "HPS";
            if (prev) {
                string tmp;
                for (char c : choices)
                    if (c != prev) tmp.push_back(c);
                choices = tmp;
            }
            char g = rnd.any(choices);
            for (int j = 0; j < len; j++)
                seq.push_back(g);
            prev = g;
        }
    } else {
        // Periodic cycle
        int c = rnd.next(1, 3);
        string cycle;
        for (int i = 0; i < c; i++)
            cycle.push_back(rnd.any(string("HPS")));
        for (int i = 0; i < N; i++)
            seq.push_back(cycle[i % c]);
    }

    // Output
    println(N, K);
    for (char c : seq)
        println(c);

    return 0;
}

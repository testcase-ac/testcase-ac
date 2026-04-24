#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: universe range for values
        int vRange = rnd.next(5, 20);
        // Universe is integers from -vRange to +vRange
        vector<int> universe;
        for (int x = -vRange; x <= vRange; ++x) {
            universe.push_back(x);
        }
        // Shuffle universe for randomness
        shuffle(universe.begin(), universe.end());

        // Size of notebook1 (distinct values)
        int maxN = min((int)universe.size(), 10);
        int N = rnd.next(1, maxN);
        vector<int> S(universe.begin(), universe.begin() + N);

        // Size of queries
        int M = rnd.next(1, 10);

        // Print notebook1
        println(N);
        println(S);

        // Probability to pick a hit vs miss
        double hitProb = rnd.next();

        // Prepare the rest of universe values (possible misses)
        vector<int> out;
        for (size_t i = N; i < universe.size(); ++i)
            out.push_back(universe[i]);

        // Generate queries
        println(M);
        vector<int> Q;
        Q.reserve(M);
        for (int i = 0; i < M; ++i) {
            int q;
            if (!S.empty() && rnd.next() < hitProb) {
                // pick a hit
                q = rnd.any(S);
            } else if (!out.empty()) {
                // pick a miss
                q = rnd.any(out);
            } else {
                // fallback to hit if no out-of-set values
                q = rnd.any(S);
            }
            Q.push_back(q);
        }
        println(Q);
    }

    return 0;
}

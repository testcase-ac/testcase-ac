#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 2 and 100, biased towards smaller sizes
    int N = rnd.wnext(99, -2) + 2;
    int threshold = (N + 1) / 2;

    // Scenario hyper-parameter:
    // 0 = all O, 1 = all X, 2 = exactly threshold O, 3 = just below threshold, 4 = random
    int scenario = rnd.next(0, 4);

    int o_count;
    if (scenario == 0) {
        o_count = N;
    } else if (scenario == 1) {
        o_count = 0;
    } else if (scenario == 2) {
        o_count = threshold;
    } else if (scenario == 3) {
        o_count = max(0, threshold - 1);
    } else {
        // Random scenario: each position independently O with random probability
        string s(N, 'X');
        double p = rnd.next(); // in [0,1)
        for (int i = 0; i < N; i++) {
            s[i] = (rnd.next() < p ? 'O' : 'X');
        }
        // Output
        println(N);
        println(s);
        return 0;
    }

    // Build string for deterministic scenarios
    string s(N, 'X');
    vector<int> pos(N);
    for (int i = 0; i < N; i++) pos[i] = i;
    shuffle(pos.begin(), pos.end());
    for (int i = 0; i < o_count; i++) {
        s[pos[i]] = 'O';
    }

    // Output
    println(N);
    println(s);

    return 0;
}

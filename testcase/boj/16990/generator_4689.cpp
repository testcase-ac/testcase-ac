#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    // Bounds for positions and directions
    int Bp = rnd.next(0, 20);
    int Bd = rnd.next(1, 5);

    // Generate patterns
    vector<string> patterns;
    for (int i = 0; i < N; i++) {
        int L = rnd.next(1, 6);
        // probability of zero for each bit
        double p0 = rnd.next(0.0, 1.0);
        string s;
        s.reserve(L);
        for (int j = 0; j < L; j++) {
            s.push_back(rnd.next() < p0 ? '0' : '1');
        }
        // enforce diversity: sometimes ensure at least one '1' or one '0'
        int mode = rnd.next(0, 2);
        if (mode == 0 && s.find('1') == string::npos) {
            s[rnd.next(0, L-1)] = '1';
        } else if (mode == 1 && s.find('0') == string::npos) {
            s[rnd.next(0, L-1)] = '0';
        }
        patterns.push_back(s);
    }

    // Generate shots
    vector<pair<int,int>> shots;
    for (int i = 0; i < M; i++) {
        int P = rnd.next(-Bp, Bp);
        int D = rnd.next(-Bd, Bd);
        shots.emplace_back(P, D);
    }

    // Shuffle shots order for randomness
    shuffle(shots.begin(), shots.end());

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println((int)patterns[i].size(), patterns[i]);
    }
    for (auto &pr : shots) {
        println(pr.first, pr.second);
    }
    return 0;
}

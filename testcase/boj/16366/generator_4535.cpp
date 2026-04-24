#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(2, 10);         // number of systems
    int C = rnd.next(1, 5);          // number of certificate types
    int H = rnd.next(1, N);          // number of human-controlled systems
    int M = rnd.next(1, N);          // number of military bases
    int W = rnd.next(1, N * 3);      // number of wormholes

    // pick human-controlled systems
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 0);
    shuffle(nodes.begin(), nodes.end());
    vector<int> humans(nodes.begin(), nodes.begin() + H);

    // pick military bases (can overlap with humans)
    shuffle(nodes.begin(), nodes.end());
    vector<int> bases(nodes.begin(), nodes.begin() + M);

    // certificate skew: pick one common certificate
    int commonCert = rnd.next(1, C);
    // self-loop probability
    double selfLoopP = rnd.next();

    // output header
    println(N, W, C, H, M);
    println(humans);
    println(bases);

    // generate edges
    for (int i = 0; i < W; i++) {
        int s, t, c;
        // decide self-loop or not
        if (rnd.next() < selfLoopP) {
            s = rnd.next(N);
            t = s;
        } else {
            s = rnd.next(N);
            t = rnd.next(N);
            if (t == s) {
                // force a different target if accidental match
                t = (s + 1) % N;
            }
        }
        // decide certificate, skewed towards commonCert
        if (rnd.next() < 0.6) {
            c = commonCert;
        } else {
            c = rnd.next(1, C);
        }
        println(s, c, t);
    }

    return 0;
}

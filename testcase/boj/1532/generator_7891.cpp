#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose an upper bound for randomness
    vector<int> sizeOpts = {10, 20, 50, 100};
    int maxVal = rnd.any(sizeOpts);

    // Case selector: 0 = trivial (no exchanges), 1 = single conversion type,
    // 2 = chain conversion (B->S->G), 3 = impossible
    int caseType = rnd.next(0, 3);

    int G1, S1, B1, G2, S2, B2;

    if (caseType == 0) {
        // Trivial: start >= target for all
        G1 = rnd.next(0, maxVal);
        G2 = rnd.next(0, G1);
        S1 = rnd.next(0, maxVal);
        S2 = rnd.next(0, S1);
        B1 = rnd.next(0, maxVal);
        B2 = rnd.next(0, B1);
    } else if (caseType == 1) {
        // Single conversion: pick one coin type to be insufficient
        int idx = rnd.next(0, 2);
        if (idx == 0) {
            // Gold deficiency, convert S->G
            G1 = rnd.next(0, maxVal);
            int d = rnd.next(1, maxVal/2 + 1);
            G2 = G1 + d;
            // need 11*S to make d gold
            S1 = 11 * d;
            S2 = rnd.next(0, S1);
            B1 = rnd.next(0, maxVal);
            B2 = rnd.next(0, B1);
        } else if (idx == 1) {
            // Silver deficiency, convert G->S
            S1 = rnd.next(0, maxVal);
            int d = rnd.next(1, maxVal/2 + 1);
            S2 = S1 + d;
            // need ceil(d/9) gold
            G1 = (d + 8) / 9;
            G2 = rnd.next(0, G1);
            B1 = rnd.next(0, maxVal);
            B2 = rnd.next(0, B1);
        } else {
            // Bronze deficiency, convert S->B
            B1 = rnd.next(0, maxVal);
            int d = rnd.next(1, maxVal/2 + 1);
            B2 = B1 + d;
            // need ceil(d/9) silver
            S1 = (d + 8) / 9;
            S2 = rnd.next(0, S1);
            G1 = rnd.next(0, maxVal);
            G2 = rnd.next(0, G1);
        }
    } else if (caseType == 2) {
        // Chain conversion: B->S->G to cover gold deficiency
        // Setup gold deficiency
        int dG = rnd.next(1, maxVal/4 + 1);
        // Gold start small
        G1 = rnd.next(0, maxVal/4);
        G2 = G1 + dG;
        // To get dG gold, need 11*dG silver
        int reqS = 11 * dG;
        // Silver start insufficient
        S1 = rnd.next(0, reqS - 1);
        S2 = rnd.next(0, S1);
        int needS = reqS - S1;
        // To get needS silver, need 11*needS bronze
        B1 = 11 * needS;
        B2 = rnd.next(0, B1);
    } else {
        // Impossible: no starting coins, positive targets
        G1 = 0; S1 = 0; B1 = 0;
        G2 = rnd.next(1, maxVal);
        S2 = rnd.next(1, maxVal);
        B2 = rnd.next(1, maxVal);
    }

    // Output the single test case
    println(G1, S1, B1);
    println(G2, S2, B2);

    return 0;
}

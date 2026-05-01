#include "testlib.h"
using namespace std;

struct Problem {
    int D, P;
    int T, E;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);
    int N = 0, M = 0;
    long long HD = 1, HP = 1;
    vector<Problem> probs;

    if (scenario == 0) {
        // Tiny random case
        N = rnd.next(1, 3);
        M = rnd.next(1, N);
        HD = rnd.next(1, 5);
        HP = rnd.next(1, 5);
        probs.resize(N);
        for (int i = 0; i < N; ++i) {
            probs[i].D = rnd.next(1, 5);
            probs[i].P = rnd.next(1, 5);
            probs[i].T = rnd.next(0, 1);
            probs[i].E = rnd.next(0, 1);
        }
    } else if (scenario == 1) {
        // Chain progression in difficulty
        N = rnd.next(4, 8);
        M = rnd.next(1, N);
        HD = rnd.next(1, 3);
        HP = rnd.next(1, 3);
        probs.resize(N);
        int curD = rnd.next((int)HD, (int)HD + 2);
        int curP = rnd.next((int)HP, (int)HP + 2);
        for (int i = 0; i < N; ++i) {
            if (i > 0) {
                curD += rnd.next(0, 2);
                curP += rnd.next(0, 2);
            }
            probs[i].D = max(1, curD);
            probs[i].P = max(1, curP);
            probs[i].T = rnd.next(0, 1);
            probs[i].E = rnd.next(0, 1);
        }
        shuffle(probs.begin(), probs.end());
    } else if (scenario == 2) {
        // Many data problems
        N = rnd.next(5, 10);
        M = rnd.next(1, N);
        HD = rnd.next(1, 5);
        HP = rnd.next(1, 5);
        probs.resize(N);
        int cntData = 0;
        for (int i = 0; i < N; ++i) {
            probs[i].D = rnd.next(1, 15);
            probs[i].P = rnd.next(1, 20);
            probs[i].T = (rnd.next(0, 99) < 70) ? 1 : 0; // 70% have data
            probs[i].E = rnd.next(0, 1);
            if (probs[i].T == 1) cntData++;
        }
        if (cntData == 0) {
            probs[0].T = 1;
        }
        shuffle(probs.begin(), probs.end());
    } else if (scenario == 3) {
        // Editorial-heavy scenario
        N = rnd.next(5, 10);
        M = rnd.next(1, N);
        HD = rnd.next(1, 4);
        HP = rnd.next(1, 4);
        probs.resize(N);
        for (int i = 0; i < N; ++i) {
            if (i < N / 2) {
                // Designed to be good editorial candidates
                int baseD = (int)(HD * 2);
                int offset = rnd.next(-2, 5);
                probs[i].D = max(1, baseD + offset);
                probs[i].P = max(1, (int)HP + rnd.next(1, 10));
                probs[i].T = rnd.next(0, 3) == 0 ? 1 : 0; // some with data
                probs[i].E = 1;
            } else {
                // Mixed remainder
                probs[i].D = rnd.next(1, 20);
                probs[i].P = rnd.next(1, 20);
                probs[i].T = rnd.next(0, 1);
                probs[i].E = rnd.next(0, 1);
            }
        }
        shuffle(probs.begin(), probs.end());
    } else if (scenario == 4) {
        // Guaranteed impossible: at least one unsolvable problem, M = N
        N = rnd.next(3, 8);
        M = N;
        HD = rnd.next(1, 5);
        HP = rnd.next(1, 5);
        probs.resize(N);
        long long maxHDpossible = HD + (N - 1);
        // Make D so large that even with maximum HD, HD*2 < D and HD < D
        long long bigD = 2 * maxHDpossible + rnd.next(1, 5);
        int idxUnsolvable = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == idxUnsolvable) {
                probs[i].D = (int)min(bigD, (long long)1000000000); // keep within 1e9
                probs[i].P = rnd.next(5, 15);
                probs[i].T = rnd.next(0, 1);
                probs[i].E = rnd.next(0, 1);
            } else {
                // Reasonably solvable problems
                int loD = max(1, (int)HD - 1);
                int hiD = (int)min(maxHDpossible, (long long)1000000000);
                if (loD > hiD) loD = hiD;
                probs[i].D = rnd.next(loD, hiD);
                probs[i].P = rnd.next(1, 15);
                probs[i].T = rnd.next(0, 1);
                probs[i].E = rnd.next(0, 1);
            }
        }
        shuffle(probs.begin(), probs.end());
    } else if (scenario == 5) {
        // Big numbers near upper bounds
        N = rnd.next(10, 15);
        M = rnd.next(1, N);
        int hdLo = 1000000000 - 100;
        if (hdLo < 1) hdLo = 1;
        HD = rnd.next(hdLo, 1000000000);
        HP = rnd.next(hdLo, 1000000000);
        probs.resize(N);
        int dLo = 1000000000 - 1000;
        if (dLo < 1) dLo = 1;
        for (int i = 0; i < N; ++i) {
            probs[i].D = rnd.next(dLo, 1000000000);
            probs[i].P = rnd.next(dLo, 1000000000);
            probs[i].T = rnd.next(0, 1);
            probs[i].E = rnd.next(0, 1);
        }
        shuffle(probs.begin(), probs.end());
    } else if (scenario == 6) {
        // Small M, need to choose best subset
        N = rnd.next(5, 10);
        M = rnd.next(1, min(3, N));
        HD = rnd.next(1, 5);
        HP = rnd.next(1, 5);
        probs.clear();

        // Two very easy, zero-penalty problems
        for (int i = 0; i < 2 && (int)probs.size() < N; ++i) {
            Problem pr;
            pr.D = rnd.next(1, (int)HD);      // solvable from start
            pr.P = rnd.next(1, (int)HP);      // no wrong submissions
            pr.T = 0;
            pr.E = rnd.next(0, 1);
            probs.push_back(pr);
        }

        // Two high-penalty but solvable problems
        for (int i = 0; i < 2 && (int)probs.size() < N; ++i) {
            Problem pr;
            pr.D = rnd.next(1, (int)(HD + 2)); // idea just around ability
            pr.P = (int)HP + rnd.next(5, 15);  // big penalty
            pr.T = 0;
            pr.E = 0;
            probs.push_back(pr);
        }

        // Remaining random mix, including some with data/editorial
        while ((int)probs.size() < N) {
            Problem pr;
            pr.D = rnd.next(1, 20);
            pr.P = rnd.next(1, 20);
            pr.T = rnd.next(0, 1);
            pr.E = rnd.next(0, 1);
            probs.push_back(pr);
        }

        shuffle(probs.begin(), probs.end());
    }

    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(probs[i].D, probs[i].P, probs[i].T, probs[i].E);
    }
    println(HD, HP);

    return 0;
}

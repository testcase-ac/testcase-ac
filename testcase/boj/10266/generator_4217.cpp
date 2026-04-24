#include "testlib.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of needles
    int n = rnd.next(2, 10);

    // Generate unique positions for clock A
    const int M = 360000;
    vector<int> A;
    unordered_set<int> usedA;
    while ((int)A.size() < n) {
        int x = rnd.next(0, M - 1);
        if (usedA.insert(x).second) {
            A.push_back(x);
        }
    }
    sort(A.begin(), A.end());

    // Decide if we want a "possible" or "impossible" case
    bool wantPossible = rnd.next(0, 1) == 1;
    vector<int> B;

    if (wantPossible) {
        // Hyper-parameter: skew rotation distribution
        int tChoice = rnd.next(-2, 2);
        int rot = rnd.wnext(M, tChoice);
        // Build B by rotating A
        for (int x : A) {
            B.push_back((x + rot) % M);
        }
    } else {
        // Build a random B until it's guaranteed impossible
        while (true) {
            B.clear();
            unordered_set<int> usedB;
            while ((int)B.size() < n) {
                int x = rnd.next(0, M - 1);
                if (usedB.insert(x).second) {
                    B.push_back(x);
                }
            }
            // Check if by any rotation A matches B
            vector<int> Bs = B, As = A;
            sort(Bs.begin(), Bs.end());
            bool matches = false;
            for (int i = 0; i < n && !matches; i++) {
                int rot = (Bs[i] - As[0] + M) % M;
                bool ok = true;
                for (int k = 0; k < n; k++) {
                    int y = (As[k] + rot) % M;
                    if (!binary_search(Bs.begin(), Bs.end(), y)) {
                        ok = false;
                        break;
                    }
                }
                if (ok) matches = true;
            }
            if (!matches) break;
        }
    }

    // Shuffle input orders
    shuffle(A.begin(), A.end());
    shuffle(B.begin(), B.end());

    // Output
    println(n);
    println(A);
    println(B);

    return 0;
}

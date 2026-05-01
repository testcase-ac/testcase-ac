#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 6);
    vector<int> Ns;

    if (scenario == 1) {
        // Single minimal test
        Ns.push_back(3);
    } else if (scenario == 2) {
        // Single maximal test
        Ns.push_back(9);
    } else if (scenario == 3) {
        // 2~5 distinct N, ascending order
        int k = rnd.next(2, 5);
        vector<int> all;
        for (int i = 3; i <= 9; ++i) all.push_back(i);
        shuffle(all.begin(), all.end());
        Ns.assign(all.begin(), all.begin() + k);
        sort(Ns.begin(), Ns.end());
    } else if (scenario == 4) {
        // 2~5 distinct N, random order
        int k = rnd.next(2, 5);
        vector<int> all;
        for (int i = 3; i <= 9; ++i) all.push_back(i);
        shuffle(all.begin(), all.end());
        Ns.assign(all.begin(), all.begin() + k);
        // Keep random order, maybe shuffle again
        shuffle(Ns.begin(), Ns.end());
    } else if (scenario == 5) {
        // 3~8 tests with guaranteed duplicates
        int T = rnd.next(3, 8);
        int base = rnd.next(3, 9);
        for (int i = 0; i < T; ++i) {
            if (i < 2) {
                Ns.push_back(base); // ensure at least one duplicate
            } else {
                Ns.push_back(rnd.next(3, 9));
            }
        }
        shuffle(Ns.begin(), Ns.end());
    } else if (scenario == 6) {
        // All N from 3 to 9 in random order
        for (int i = 3; i <= 9; ++i) Ns.push_back(i);
        shuffle(Ns.begin(), Ns.end());
    }

    int T = (int)Ns.size();
    if (T == 0) {
        // Fallback (should not happen)
        Ns.push_back(9);
        T = 1;
    }

    println(T);
    for (int x : Ns) println(x);

    return 0;
}

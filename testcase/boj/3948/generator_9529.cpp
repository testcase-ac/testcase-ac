#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> Ns;

    int pattern = rnd.next(0, 4);

    if (pattern == 0) {
        // Single test, focus on interesting Ns
        vector<int> candidates = {1, 2, 3, 4, 5, 10, 15, 20};
        Ns.push_back(rnd.any(candidates));
    } else if (pattern == 1) {
        // Small range coverage from 1..maxN
        int maxN = rnd.next(5, 12); // up to 12 to stay compact
        for (int i = 1; i <= maxN; ++i)
            Ns.push_back(i);
        if (rnd.next(0, 1))
            shuffle(Ns.begin(), Ns.end());
    } else if (pattern == 2) {
        // Many random tests with duplicates, ensure extremes 1 and 20 included
        int T = rnd.next(10, 25);
        Ns.reserve(T);
        for (int i = 0; i < T; ++i)
            Ns.push_back(rnd.next(1, 20));

        // Ensure at least one 1 and one 20
        bool has1 = false, has20 = false;
        for (int x : Ns) {
            if (x == 1) has1 = true;
            if (x == 20) has20 = true;
        }
        if (!has1) Ns[rnd.next((int)Ns.size())] = 1;
        if (!has20) Ns[rnd.next((int)Ns.size())] = 20;
    } else if (pattern == 3) {
        // All same N, sometimes extreme, sometimes random
        int T = rnd.next(2, 15);
        int N;
        if (rnd.next(0, 1)) {
            // Force extreme
            N = (rnd.next(0, 1) ? 1 : 20);
        } else {
            N = rnd.next(1, 20);
        }
        Ns.assign(T, N);
    } else {
        // Mixed: some small, some large, some repeats
        int T = rnd.next(5, 18);
        Ns.reserve(T);
        for (int i = 0; i < T; ++i) {
            int choice = rnd.next(0, 3);
            if (choice == 0)
                Ns.push_back(rnd.next(1, 5));      // bias to small
            else if (choice == 1)
                Ns.push_back(rnd.next(6, 12));
            else
                Ns.push_back(rnd.next(13, 20));    // include larger
        }
        // Randomly insert a known tricky size (like 3 or 4)
        Ns[rnd.next((int)Ns.size())] = rnd.any(vector<int>{3, 4});
    }

    int T = (int)Ns.size();
    println(T);
    for (int x : Ns)
        println(x);

    return 0;
}

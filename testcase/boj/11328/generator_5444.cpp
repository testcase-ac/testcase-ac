#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small and hand-checkable
    const int MX = 5;
    int N = rnd.next(1, MX);
    println(N);

    for (int tc = 0; tc < N; ++tc) {
        // Hyper-parameter 1: length of base string S
        int L = rnd.next(1, MX);
        string s;
        s.reserve(L);
        for (int i = 0; i < L; ++i) {
            char c = char(rnd.next('a', 'z'));
            s.push_back(c);
        }

        // Hyper-parameter 2: probability that we generate a "Possible" case
        double possibleProb = rnd.next(0.0, 1.0);
        bool isPossible = (rnd.next() < possibleProb);

        if (isPossible) {
            // Generate a valid permutation of s
            string t = s;
            shuffle(t.begin(), t.end());
            println(s, t);
        } else {
            // Hyper-parameter 3: probability that the failure is by length mismatch
            double lengthMismatchProb = rnd.next(0.0, 1.0);
            if (rnd.next() < lengthMismatchProb) {
                // Generate a string of different length
                int L2 = rnd.next(1, MX);
                while (L2 == L) {
                    L2 = rnd.next(1, MX);
                }
                string t2;
                t2.reserve(L2);
                for (int i = 0; i < L2; ++i) {
                    char c = char(rnd.next('a', 'z'));
                    t2.push_back(c);
                }
                println(s, t2);
            } else {
                // Generate a string of the same length but different character multiset
                string t2 = s;
                int pos = rnd.next(0, L - 1);
                char newc;
                do {
                    newc = char(rnd.next('a', 'z'));
                } while (newc == t2[pos]);
                t2[pos] = newc;
                println(s, t2);
            }
        }
    }

    return 0;
}

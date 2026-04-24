#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 20);
    println(T);

    // Global hyperparameters
    double globalP = rnd.next(0.0, 1.0);    // bias for 1 in random type
    int maxHalf = rnd.next(1, 5);          // half-length bound, so max length = 2 * maxHalf

    for (int ti = 0; ti < T; ti++) {
        // Choose even length string
        int half = rnd.next(1, maxHalf);
        int L = half * 2;

        // Three pattern types for diversity:
        // 0 = random biased string
        // 1 = palindrome (always Do-it)
        // 2 = alternating bits (always Do-it-Not)
        int type = rnd.next(0, 2);
        string s;
        s.reserve(L);

        if (type == 0) {
            // Random biased string
            for (int i = 0; i < L; i++) {
                char c = (rnd.next() < globalP ? '1' : '0');
                s.push_back(c);
            }
        } else if (type == 1) {
            // Palindrome
            for (int i = 0; i < half; i++) {
                char c = rnd.any(string("01"));
                s.push_back(c);
            }
            string rev = s;
            reverse(rev.begin(), rev.end());
            s += rev;
        } else {
            // Alternating bits
            char start = rnd.any(string("01"));
            for (int i = 0; i < L; i++) {
                if (i % 2 == 0)
                    s.push_back(start);
                else
                    s.push_back(start == '0' ? '1' : '0');
            }
        }

        // Output the test string
        println(s);
    }

    return 0;
}

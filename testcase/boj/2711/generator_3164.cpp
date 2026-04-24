#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int t = 0; t < T; t++) {
        // Length of the string
        int L = rnd.next(1, 10);
        // Alphabet size (use first a_sz uppercase letters)
        int a_sz = rnd.next(1, 26);
        // Build string with occasional repeats
        string s;
        s.reserve(L);
        for (int i = 0; i < L; i++) {
            if (i > 0 && rnd.next() < 0.1) {
                // repeat previous character
                s.push_back(s.back());
            } else {
                s.push_back(char('A' + rnd.next(a_sz)));
            }
        }
        // Bias for typo position: -2 for early, 0 for uniform, +2 for late
        vector<int> biases = { -2, 0, 2 };
        int bias = rnd.any(biases);
        // Generate a weighted position in [0, L-1], then shift to [1, L]
        int raw = rnd.wnext(L, bias);
        int pos = raw + 1;
        // Output test case
        println(pos, s);
    }
    return 0;
}

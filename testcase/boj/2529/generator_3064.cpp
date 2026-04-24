#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of inequalities
    int k = rnd.next(2, 9);
    vector<char> a(k);

    // Choose a mode for diversity
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Independent random '<' or '>'
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < k; i++) {
            a[i] = rnd.next() < p ? '<' : '>';
        }
    } else if (mode == 1) {
        // All same symbol
        char c = rnd.any(string("<>"));
        for (int i = 0; i < k; i++) a[i] = c;
    } else if (mode == 2) {
        // Strict alternating
        char c = rnd.any(string("<>"));
        for (int i = 0; i < k; i++) {
            a[i] = c;
            c = (c == '<' ? '>' : '<');
        }
    } else {
        // Random blocks of alternating symbols
        int blocks = rnd.next(2, min(k, 4));
        vector<int> sizes(blocks, 1);
        int rem = k - blocks;
        while (rem > 0) {
            sizes[rnd.next(0, blocks - 1)]++;
            rem--;
        }
        char c = rnd.any(string("<>"));
        int pos = 0;
        for (int b = 0; b < blocks; b++) {
            for (int j = 0; j < sizes[b]; j++) {
                a[pos++] = c;
            }
            c = (c == '<' ? '>' : '<');
        }
    }

    // Output
    println(k);
    println(a);

    return 0;
}

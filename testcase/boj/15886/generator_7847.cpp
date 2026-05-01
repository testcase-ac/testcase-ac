#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose overall size category
    int N;
    double p = rnd.next();
    if (p < 0.3) {
        // small
        N = rnd.next(2, 10);
    } else if (p < 0.75) {
        // medium
        N = rnd.next(11, 100);
    } else {
        // large (but keep under 300 for readability)
        N = rnd.next(101, 300);
    }

    // Choose a pattern type for variability
    int type = rnd.next(0, 3);
    // Build the map
    string s(N, 'E');
    s[0] = 'E';
    s[N-1] = 'W';
    if (type == 0) {
        // fully random interior
        for (int i = 1; i < N-1; i++) {
            s[i] = rnd.next(0, 1) ? 'E' : 'W';
        }
    } else if (type == 1) {
        // monotonic E then single W at end (one big cycle)
        for (int i = 1; i < N-1; i++) {
            s[i] = 'E';
        }
    } else if (type == 2) {
        // alternating to form many small 2-cycles
        for (int i = 1; i < N-1; i++) {
            // make pairs (0-1), (2-3), ...
            s[i] = (i % 2 == 1 ? 'W' : 'E');
        }
    } else {
        // random blocks: occasionally flip direction
        char cur = 'E';
        for (int i = 1; i < N-1; i++) {
            if (rnd.next(1, 10) == 1) {
                cur = (cur == 'E' ? 'W' : 'E');
            }
            s[i] = cur;
        }
    }

    // Output
    println(N);
    printf("%s\n", s.c_str());

    return 0;
}

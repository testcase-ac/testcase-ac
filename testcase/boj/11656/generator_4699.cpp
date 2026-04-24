#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for length distribution: skewed to small or large
    int t_len = rnd.next(-1, 1);
    int n = rnd.wnext(10, t_len) + 1;  // length in [1,10]

    // Hyper-parameter for alphabet size: skewed selection
    int t_alpha = rnd.next(-2, 2);
    int alpha_size = rnd.wnext(26, t_alpha) + 1;  // size in [1,26]
    char min_c = 'a';

    // Choose generation mode: random, periodic, sorted, reverse-sorted
    int mode = rnd.next(1, 4);
    string s;
    s.resize(n);

    if (mode == 2) {
        // Periodic string
        int m = rnd.next(1, n);
        string motif;
        motif.resize(m);
        for (int i = 0; i < m; i++) {
            motif[i] = min_c + rnd.next(alpha_size);
        }
        for (int i = 0; i < n; i++) {
            s[i] = motif[i % m];
        }
    } else {
        // Generate random string
        for (int i = 0; i < n; i++) {
            s[i] = min_c + rnd.next(alpha_size);
        }
        if (mode == 3) {
            sort(s.begin(), s.end());
        } else if (mode == 4) {
            sort(s.begin(), s.end());
            reverse(s.begin(), s.end());
        }
    }

    // Output the single test string
    println(s);
    return 0;
}

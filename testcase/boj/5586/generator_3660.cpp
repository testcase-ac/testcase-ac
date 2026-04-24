#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the string
    int N = rnd.next(1, 20);

    // Prepare an all-random uppercase string
    string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s;
    s.resize(N);
    for (int i = 0; i < N; i++) {
        s[i] = rnd.any(alph);
    }

    // Choose scenario type for diversity
    int type = rnd.next(0, 3);
    if (N >= 3) {
        if (type == 1) {
            // Embed several JOI patterns
            int maxK = max(1, N / 3);
            int k = rnd.next(1, maxK);
            for (int i = 0; i < k; i++) {
                int pos = rnd.next(0, N - 3);
                s[pos] = 'J';
                s[pos + 1] = 'O';
                s[pos + 2] = 'I';
            }
        } else if (type == 2) {
            // Embed several IOI patterns
            int maxK = max(1, N / 3);
            int k = rnd.next(1, maxK);
            for (int i = 0; i < k; i++) {
                int pos = rnd.next(0, N - 3);
                s[pos] = 'I';
                s[pos + 1] = 'O';
                s[pos + 2] = 'I';
            }
        } else if (type == 3) {
            // Embed a mix of JOI and IOI
            int maxK = max(1, N / 3);
            int k = rnd.next(1, maxK);
            for (int i = 0; i < k; i++) {
                int pos = rnd.next(0, N - 3);
                if (rnd.next(0, 1) == 0) {
                    s[pos] = 'J';
                    s[pos + 1] = 'O';
                    s[pos + 2] = 'I';
                } else {
                    s[pos] = 'I';
                    s[pos + 1] = 'O';
                    s[pos + 2] = 'I';
                }
            }
        }
        // type 0 leaves it fully random
    }

    // Output the generated string
    printf("%s\n", s.c_str());
    return 0;
}

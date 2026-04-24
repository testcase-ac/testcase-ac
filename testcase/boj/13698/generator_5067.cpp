#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sequence length hyper-parameter
    int L = rnd.next(1, 20);
    // Choose generation mode: 0 = uniform, 1 = weighted bias, 2 = block runs
    int mode = rnd.next(0, 2);
    string s;
    if (mode == 2) {
        // Block mode: runs of same swap
        while ((int)s.size() < L) {
            int idx = rnd.next(0, 5);
            int rem = L - (int)s.size();
            int block = rnd.next(1, min(5, rem));
            for (int i = 0; i < block; i++)
                s.push_back(char('A' + idx));
        }
    } else {
        // Letter-by-letter
        int t = 0;
        if (mode == 1) {
            // bias parameter for weighted next
            t = rnd.next(-2, 2);
        }
        for (int i = 0; i < L; i++) {
            int idx;
            if (mode == 0) {
                idx = rnd.next(0, 5);
            } else {
                // weighted bias over [0,5]
                idx = rnd.wnext(6, t);
            }
            s.push_back(char('A' + idx));
        }
    }
    // Output the sequence of swaps
    printf("%s\n", s.c_str());
    return 0;
}

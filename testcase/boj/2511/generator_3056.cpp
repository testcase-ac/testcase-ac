#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base deck of cards 0..9
    vector<int> base(10);
    iota(base.begin(), base.end(), 0);

    // Generate A's permutation
    vector<int> A = base;
    shuffle(A.begin(), A.end());

    // Choose generation mode for B to diversify cases
    // 0: identical decks (full draw)
    // 1: reversed deck (mirrored sequence)
    // 2: independent random deck
    // 3: same prefix, shuffled suffix
    int mode = rnd.next(0, 3);
    vector<int> B;
    switch (mode) {
        case 0:
            B = A;
            break;
        case 1:
            B = A;
            reverse(B.begin(), B.end());
            break;
        case 2:
            B = base;
            shuffle(B.begin(), B.end());
            break;
        case 3:
        default:
            B = A;
            {
                // copy prefix of length k, shuffle the rest
                int k = rnd.next(1, 9);
                shuffle(B.begin() + k, B.end());
            }
            break;
    }

    // Output two lines: A's deck and B's deck
    println(A);
    println(B);

    return 0;
}

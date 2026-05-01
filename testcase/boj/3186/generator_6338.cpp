#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose sequence length small enough for manual checking, but variable
    int N = rnd.next(1, 30);

    // Sometimes force all 0s or all 1s to catch edge cases
    string seq;
    int roll = rnd.next(0, 4);
    if (roll == 0) {
        seq = string(N, '0');
    } else if (roll == 1) {
        seq = string(N, '1');
    } else {
        // Build runs of 0s and 1s with random block count
        int blocks = rnd.next(1, min(5, N));
        vector<int> lens(blocks, 1);
        int rem = N - blocks;
        while (rem > 0) {
            int i = rnd.next(0, blocks - 1);
            lens[i]++;
            rem--;
        }
        // Randomly alternate block types
        char cur = rnd.any(string("01"));
        vector<char> types(blocks);
        for (int i = 0; i < blocks; i++) {
            types[i] = cur;
            if (rnd.next(0, 1)) cur = (cur == '0' ? '1' : '0');
        }
        // Build the full sequence
        seq.clear();
        for (int i = 0; i < blocks; i++)
            seq += string(lens[i], types[i]);
    }

    // Choose K and L relative to N, but allow K > N (no usage) and small L
    int K = rnd.next(1, min(1000, N + 5));
    int L = rnd.next(1, min(1000, N + 5));

    // Output
    printf("%d %d %d\n", K, L, N);
    printf("%s\n", seq.c_str());
    return 0;
}

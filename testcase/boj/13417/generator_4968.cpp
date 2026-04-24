#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Size of this test
        int N = rnd.next(1, 10);

        // Choose a small alphabet size
        int maxAlpha = min(N, 5);
        int K = rnd.next(1, maxAlpha);

        // Sample K distinct uppercase letters
        vector<char> pool;
        for (char c = 'A'; c <= 'Z'; ++c) pool.push_back(c);
        shuffle(pool.begin(), pool.end());
        vector<char> letters(pool.begin(), pool.begin() + K);

        // Choose generation style
        int genType = rnd.next(0, 3);
        vector<char> seq(N);

        if (genType == 0) {
            // Completely random picks
            for (int i = 0; i < N; i++)
                seq[i] = rnd.any(letters);
        } else if (genType == 1) {
            // Sorted sequence
            for (int i = 0; i < N; i++)
                seq[i] = rnd.any(letters);
            sort(seq.begin(), seq.end());
        } else if (genType == 2) {
            // Reverse sorted
            for (int i = 0; i < N; i++)
                seq[i] = rnd.any(letters);
            sort(seq.begin(), seq.end(), greater<char>());
        } else {
            // Blocky pattern
            int maxBlock = rnd.next(1, N);
            int i = 0;
            while (i < N) {
                char c = rnd.any(letters);
                int len = rnd.next(1, maxBlock);
                for (int j = 0; j < len && i < N; j++, i++)
                    seq[i] = c;
            }
        }

        // Output this test case
        println(N);
        // print with spaces
        for (int i = 0; i < N; i++) {
            printf("%c", seq[i]);
            if (i + 1 < N) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
